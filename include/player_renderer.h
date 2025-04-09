#pragma once

#include "game.h"
#include "timer.h"

#include <SDL3/SDL.h>
#include <vector>

class PlayerRenderer
{
private:
    enum class Direction : uint8_t
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

    enum class SpriteIndex : uint8_t
    {
        IDLE_DOWN_FIRST = 0,
        IDLE_RIGHT_FIRST = 6,
        IDLE_UP_FIRST = 12,
        MOVE_DOWN_FIRST = 18,
        MOVE_RIGHT_FIRST = 24,
        MOVE_UP_FIRST = 30,
        DEAD_FIRST = 36,
        DEAD_LAST = 38,
    };

public:
    PlayerRenderer(const Entity &player);
    ~PlayerRenderer();

    void render(double timeSinceLastRender);

private:
    static constexpr const char *SPRITE_PATH = "assets/sprites/player.png";
    static constexpr uint8_t SPRITE_SIZE = 48;
    static constexpr uint8_t COUNT_FRAME_ANIM = 6;
    static constexpr uint8_t COUNT_FRAME_DEAD = 3;
    static constexpr uint8_t VEC_SIZE = 39;
    static constexpr uint8_t ANIM_ROWS = 6;
    static constexpr double FRAME_TIME_ANIM = 0.2;

    const Entity &player;
    SDL_Texture *texture;
    std::vector<SDL_FRect> spritesRect;

    void genRect();
    SDL_FRect *selectFrameRect();

    SDL_FRect destRect;
    Direction direction;
    bool flip;
    Timer animationTimer;
    uint8_t animationFrame;
    uint8_t deadFrame;
};
