#pragma once

#include "game.h"
#include "i_game_renderer.h"
#include "player_renderer.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class GameRenderer : public IGameRenderer
{
public:
    GameRenderer(Game &game);
    ~GameRenderer();

    void render(double alpha, double timeSinceLastRender);

private:
    static constexpr SDL_Color WHITE = {255, 255, 255, SDL_ALPHA_OPAQUE};
    static constexpr SDL_Color RED = {255, 0, 0, SDL_ALPHA_OPAQUE};
    static constexpr SDL_Color BLUE = {0, 0, 255, SDL_ALPHA_OPAQUE};
    static constexpr float HEALTH_BAR_HEIGHT_SCALE = 0.015f;
    static constexpr float HEALTH_BAR_WIDTH_SCALE = 0.8f;
    static constexpr float HEALTH_BAR_POS_X_SCALE = 0.05f;
    static constexpr float HEALTH_BAR_POS_Y_SCALE = 0.05f;
    static constexpr float END_GAME_POS_X_SCALE = 0.5f;
    static constexpr float END_GAME_POS_Y_SCALE = 0.5f;

    Game &game;
    PlayerRenderer playerRenderer;

    float getHealthWidth(const Entity &player);

    float healthBarWidth;
    SDL_Texture *textTexture;
    SDL_FRect healthBarRect;
    SDL_FRect healthRect;
    SDL_FRect endGameRect;
};