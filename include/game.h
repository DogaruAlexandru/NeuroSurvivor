#pragma once

#include "i_script_manager.h"
#include "input_handler.h"
#include "game_objects/enemy.h"
#include "game_objects/player.h"
#include "game_objects/projectile.h"

#include <cstdint>
#include <deque>
#include <memory>
#include <vector>

class Game
{
  friend class GameAPI;

public:
  Game(InputHandler &inputHandler,
       std::shared_ptr<IScriptManager> scriptManager);
  ~Game() = default;

  void update(double deltaTime);

  Player &getPlayer();
  std::vector<Enemy> &getEnemies();
  std::deque<Projectile> &getProjectiles();

private:
  int16_t enemyCount = 16;
  InputHandler &inputHandler;
  double deltaTime;

  std::shared_ptr<IScriptManager> scriptManager;

  Player player;
  std::vector<Enemy> enemies;
  std::deque<Projectile> projectiles;

  void enemiesUpdate();
  void projectileUpdate();
};
