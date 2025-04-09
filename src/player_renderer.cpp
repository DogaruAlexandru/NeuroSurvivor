#include "player_renderer.h"
#include "render_utils.h"
#include "camera.h"

PlayerRenderer::PlayerRenderer(const Entity &player)
    : player(player),
      animationFrame(0),
      deadFrame(0),
      direction(Direction::DOWN),
      flip(false),
      animationTimer(FRAME_TIME_ANIM),
      destRect({static_cast<float>(Camera::getInstance().getScreenCenterX() - player.getRadius()), static_cast<float>(Camera::getInstance().getScreenCenterY() - player.getRadius()), static_cast<float>(player.getRadius() * 2.0), static_cast<float>(player.getRadius() * 2.0)}),
      spritesRect(VEC_SIZE, SDL_FRect{0, 0, static_cast<float>(SPRITE_SIZE), static_cast<float>(SPRITE_SIZE)})
{
    texture = RenderUtils::getInstance().initTexture(SPRITE_PATH);
    genRect();
}

PlayerRenderer::~PlayerRenderer()
{
    SDL_DestroyTexture(texture);
}

void PlayerRenderer::render(double timeSinceLastRender)
{
    if (flip)
    {
        RenderUtils::getInstance().renderTextureFliped(texture, selectFrameRect(), &destRect);
    }
    else
    {
        RenderUtils::getInstance().renderTexture(texture, selectFrameRect(), &destRect);
    }

    animationTimer.update(timeSinceLastRender);
}

void PlayerRenderer::genRect()
{
    auto generateAnimationRects = [&](uint8_t startIndex, uint8_t rowOffset, uint8_t frameCount)
    {
        for (uint8_t j = 0; j < frameCount; j++)
        {
            uint8_t index = startIndex + j;
            spritesRect[index].x = j * SPRITE_SIZE;
            spritesRect[index].y = rowOffset * SPRITE_SIZE;
        }
    };

    // Generate rectangles for normal animations
    for (uint8_t i = 0; i < ANIM_ROWS; i++)
    {
        generateAnimationRects(COUNT_FRAME_ANIM * i, i, COUNT_FRAME_ANIM);
    }

    // Generate rectangles for the "dead" animation
    generateAnimationRects(static_cast<uint8_t>(SpriteIndex::DEAD_FIRST), ANIM_ROWS, COUNT_FRAME_DEAD);
}

SDL_FRect *PlayerRenderer::selectFrameRect()
{
    // Handle "dead" animation
    if (player.getHealth() <= 0)
    {
        if (deadFrame < COUNT_FRAME_DEAD)
        {
            SDL_FRect *deadRect = &spritesRect[static_cast<size_t>(SpriteIndex::DEAD_FIRST) + deadFrame];
            if (animationTimer.isFinished())
            {
                ++deadFrame;
                animationTimer.reset();
            }
            return deadRect;
        }
        return &spritesRect[static_cast<size_t>(SpriteIndex::DEAD_LAST)];
    }

    // Handle normal animations
    if (animationTimer.isFinished())
    {
        animationFrame = (animationFrame + 1) % COUNT_FRAME_ANIM;
        animationTimer.reset();
    }

    if (player.getVelocityY() > 0)
    {
        direction = Direction::DOWN;
        flip = false;
        return &spritesRect[static_cast<size_t>(SpriteIndex::MOVE_DOWN_FIRST) + animationFrame];
    }
    else if (player.getVelocityY() < 0)
    {
        direction = Direction::UP;
        flip = false;
        return &spritesRect[static_cast<size_t>(SpriteIndex::MOVE_UP_FIRST) + animationFrame];
    }
    else if (player.getVelocityX() > 0)
    {
        direction = Direction::RIGHT;
        flip = false;
        return &spritesRect[static_cast<size_t>(SpriteIndex::MOVE_RIGHT_FIRST) + animationFrame];
    }
    else if (player.getVelocityX() < 0)
    {
        direction = Direction::LEFT;
        flip = true;
        return &spritesRect[static_cast<size_t>(SpriteIndex::MOVE_RIGHT_FIRST) + animationFrame];
    }
    else
    {
        switch (direction)
        {
        case Direction::UP:
            return &spritesRect[static_cast<size_t>(SpriteIndex::IDLE_UP_FIRST) + animationFrame];
        case Direction::DOWN:
            return &spritesRect[static_cast<size_t>(SpriteIndex::IDLE_DOWN_FIRST) + animationFrame];
        case Direction::LEFT:
        case Direction::RIGHT:
            return &spritesRect[static_cast<size_t>(SpriteIndex::IDLE_RIGHT_FIRST) + animationFrame];
        }
    }
    return nullptr;
}
