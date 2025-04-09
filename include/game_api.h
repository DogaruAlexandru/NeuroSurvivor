#pragma once

#include <game.h>

class GameAPI
{
  Game *game;

public:
  GameAPI(Game *game);
  Entity &getPlayer();
};
