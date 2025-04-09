#include "game_loop.h"
#include "python_script_manager.h"

GameLoop::GameLoop()
    : inputHandler(),
      scriptManager(std::make_shared<PythonScriptManager>(&game)),
      game(inputHandler, scriptManager), gameRenderer(game),
      lastFrameTime(SDL_GetPerformanceCounter()), timeSinceLastUpdate(0.0),
      timeSinceLastRender(0.0) {}

void GameLoop::iterate() {
  int64_t currentTime = SDL_GetPerformanceCounter();

  double deltaTime = static_cast<double>(currentTime - lastFrameTime) /
                     SDL_GetPerformanceFrequency();
  lastFrameTime = currentTime;

  timeSinceLastUpdate += deltaTime;

  // Update game logic in fixed time steps
  while (timeSinceLastUpdate >= UPDATE_TIME) {
    game.update(UPDATE_TIME);
    timeSinceLastUpdate -= UPDATE_TIME;
  }

  // Interpolation factor for smooth rendering
  double alpha = timeSinceLastUpdate / UPDATE_TIME;

  // Limit render frequency
  timeSinceLastRender += deltaTime;
  if (timeSinceLastRender >= FRAME_TIME) {
    gameRenderer.render(
        alpha, timeSinceLastRender); // Use interpolation for smooth rendering
    timeSinceLastRender = 0.0;
  }
}

SDL_AppResult GameLoop::handleEvent(SDL_Event *event) {
  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;

  case SDL_EVENT_KEY_DOWN:
    if (event->key.scancode == SDL_SCANCODE_ESCAPE) {
      return SDL_APP_SUCCESS;
    }
    inputHandler.addKeyInput(event->key.scancode);
    break;

  case SDL_EVENT_KEY_UP:
    inputHandler.removeKeyInput(event->key.scancode);
    break;

  case SDL_EVENT_MOUSE_BUTTON_DOWN:
    inputHandler.addMouseInput(event->button.x, event->button.y,
                               event->button.button);
    break;

  case SDL_EVENT_MOUSE_BUTTON_UP:
    inputHandler.removeMouseInput(event->button.button);
    break;

  case SDL_EVENT_MOUSE_MOTION:
    inputHandler.updateMousePosition(event->motion.x, event->motion.y);
    break;

  default:
    break;
  }
  return SDL_APP_CONTINUE;
}

IInputHandler &GameLoop::getInputHandler() { return inputHandler; }
