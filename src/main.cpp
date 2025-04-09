#define SDL_MAIN_USE_CALLBACKS

#include "game_loop.h"
#include "render_utils.h"
#include "camera.h"

#include <SDL3/SDL_main.h>

struct AppState
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    GameLoop *gameLoop;
};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
    if (!SDL_SetAppMetadata("LLM Game", "1.0", "com.example.game"))
    {
        return SDL_APP_FAILURE;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != true)
    {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    AppState *state = (AppState *)SDL_calloc(1, sizeof(AppState));
    if (!state)
    {
        SDL_Log("Failed to allocate AppState");
        return SDL_APP_FAILURE;
    }

    SDL_DisplayID displayID = SDL_GetPrimaryDisplay();
    const SDL_DisplayMode *displayMode = SDL_GetCurrentDisplayMode(displayID);
    if (!displayMode)
    {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    state->window = SDL_CreateWindow("LLM Game", displayMode->w, displayMode->h, SDL_WINDOW_BORDERLESS);
    if (!state->window)
    {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    Camera::getInstance().setScreenSize(displayMode->w, displayMode->h);

    state->renderer = SDL_CreateRenderer(state->window, "Software");
    if (!state->renderer)
    {
        SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!RenderUtils::init(state->renderer))
    {
        SDL_Log("Failed to initialize RenderUtils");
        return SDL_APP_FAILURE;
    }

    state->gameLoop = new GameLoop();
    if (!state->gameLoop)
    {
        SDL_Log("Failed to create GameLoop");
        return SDL_APP_FAILURE;
    }

    *appstate = state;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    AppState *state = (AppState *)appstate;

    state->gameLoop->iterate();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    AppState *state = (AppState *)appstate;

    return state->gameLoop->handleEvent(event);
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    AppState *state = (AppState *)appstate;
    if (state)
    {
        if (state->renderer)
        {
            SDL_DestroyRenderer(state->renderer);
        }
        if (state->window)
        {
            SDL_DestroyWindow(state->window);
        }
        if (state->gameLoop)
        {
            delete state->gameLoop;
        }
        SDL_free(state);
    }
    SDL_Quit();
}
