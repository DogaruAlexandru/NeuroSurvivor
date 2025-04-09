#include "game_api.h"

GameAPI::GameAPI(Game *game)
    : game(game)
{
}

Entity &GameAPI::getPlayer()
{
    return game->getPlayer();
}