#pragma once

#include "game.h"
#include "game_renderer.h"
#include "i_script_manager.h"
#include "input_handler.h"

#include <SDL3/SDL.h>
#include <memory>

class GameLoop {
public:
  GameLoop();

  void iterate();
  SDL_AppResult handleEvent(SDL_Event *event);
  IInputHandler &getInputHandler();

private:
  static constexpr double UPS = 60.0;              // Fixed updates per second
  static constexpr double UPDATE_TIME = 1.0 / UPS; // Fixed time per update
  static constexpr double FPS = 60.0;              // Frames per second
  static constexpr double FRAME_TIME = 1.0 / FPS;  // Time per frame

  std::shared_ptr<IScriptManager> scriptManager;
  Game game;
  InputHandler inputHandler;
  GameRenderer gameRenderer;

  int64_t lastFrameTime;

  double timeSinceLastUpdate;
  double timeSinceLastRender;
};
