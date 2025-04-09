#include "game.h"
#include "camera.h"

#include <cmath>
#include <algorithm>
#include <cmath>

Game::Game(InputHandler &inputHandler, std::shared_ptr<IScriptManager> scriptManager)
    : inputHandler(inputHandler), player(Player(0.0, 0.0)), scriptManager(scriptManager)
{
  enemies.reserve(enemyCount);
  for (int i = 0; i < enemyCount; i++)
  {
    enemies.emplace_back();
  }
}

void Game::update(double deltaTime)
{
  this->deltaTime = deltaTime;

  if (player.isAlive())
  {
    player.update(deltaTime, inputHandler.getMoveInput(), inputHandler.getActionInput(), projectiles);
  }
  projectileUpdate();
  enemiesUpdate();
}

void Game::enemiesUpdate()
{
  const double radius = player.getColisionRadius();
  for (auto it = enemies.begin(); it != enemies.end(); ++it)
  {
    if (!it->isAlive())
    {
      it->setOutsidePos();
      it->setHealth(it->getMaxHealth());
      continue;
    }

    double dx = player.getX() - it->getX();
    double dy = player.getY() - it->getY();
    double distance = std::sqrt(dx * dx + dy * dy);

    // Resolve overlap with the player
    if (distance < it->getColisionRadius() + radius)
    {
      double overlap = it->getColisionRadius() + radius - distance;
      double adjustX = (dx / distance) * overlap;
      double adjustY = (dy / distance) * overlap;

      // Push the enemy away from the player
      it->setPosition(it->getX() - adjustX, it->getY() - adjustY);
    }

    if (distance > it->getColisionRadius() + radius)
    {
      it->setVelocity((dx / distance) * it->getMaxSpeed(), (dy / distance) * it->getMaxSpeed());
    }

    // Check for collisions with other enemies
    for (auto other = enemies.begin(); other != enemies.end(); ++other)
    {
      if (it == other || !other->isAlive())
        continue;

      double otherDx = other->getX() - it->getX();
      double otherDy = other->getY() - it->getY();
      double otherDistance = std::sqrt(otherDx * otherDx + otherDy * otherDy);

      if (otherDistance < it->getColisionRadius() + other->getColisionRadius())
      {
        // Resolve collision by adjusting velocities
        double overlap = it->getColisionRadius() + other->getColisionRadius() - otherDistance;
        double adjustX = (otherDx / otherDistance) * overlap / 2;
        double adjustY = (otherDy / otherDistance) * overlap / 2;

        it->setPosition(it->getX() - adjustX, it->getY() - adjustY);
        other->setPosition(other->getX() + adjustX, other->getY() + adjustY);
      }
    }

    it->move(deltaTime);
    if (it->collidesWith(player))
    {
      player.takeDamage(it->getMeleeDamage());
    }
  }
}

void Game::projectileUpdate()
{
  // Remove all projectiles that should be removed.
  projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](const Projectile &proj)
                                   { return proj.getShouldRemove(); }),
                    projectiles.end());

  // Update all projectiles.
  for (auto &proj : projectiles)
  {
    proj.move(deltaTime);

    for (auto &enemy : enemies)
    {
      if (proj.collidesWith(enemy))
      {
        enemy.takeDamage(proj.getDamage());
        proj.setShouldRemove(true);
      }
    }
  }
}

std::vector<Enemy> &Game::getEnemies()
{
  return enemies;
}

Player &Game::getPlayer() { return player; }

std::deque<Projectile> &Game::getProjectiles() { return projectiles; }
