#include "game_objects/player.h"
#include "camera.h"

Player::Player(double x, double y, double scaleVelocityX, double scaleVelocityY, double scaleRadius, double scaleColisionRadius, double scaleMaxSpeed, double health, double maxHealth)
    : Entity(x, y, scaleVelocityX, scaleVelocityY, scaleRadius, scaleColisionRadius, scaleMaxSpeed, health, maxHealth), invulnerabilityTimer(INVULNERABILITY_TIME), item(std::make_shared<Item>())
{
    Camera::getInstance().setWorldCenter(x, y);
}

Player::Player(double x, double y)
    : Player(x, y, 0.0, 0.0, RADIUS, COLISION_RADIUS, MAX_SPEED, HEALTH, MAX_HEALTH)
{
}

void Player::update(double deltaTime, std::vector<bool> &moveInput, std::vector<MouseInputInfo> &actionInput, std::deque<Projectile> &projectiles)
{
    setVelocity(moveInput);
    move(deltaTime);
    Camera::getInstance().setWorldCenter(x, y);
    handleWeaponActions(actionInput, projectiles);
    item->update(deltaTime);

    invulnerabilityTimer.update(deltaTime);
}

void Player::setVelocity(std::vector<bool> &moveInput)
{
    velocityX = 0;
    velocityY = 0;

    for (size_t i = 0; i < moveInput.size(); ++i)
    {
        if (moveInput[i])
        {
            switch (static_cast<KeyInputType>(i))
            {
            case KeyInputType::up:
                velocityY -= 1.0;
                break;
            case KeyInputType::down:
                velocityY += 1.0;
                break;
            case KeyInputType::left:
                velocityX -= 1.0;
                break;
            case KeyInputType::right:
                velocityX += 1.0;
                break;
            }
        }
    }

    // Apply player speed
    velocityX *= maxSpeed;
    velocityY *= maxSpeed;

    // Normalize diagonal movement
    if (velocityX != 0 && velocityY != 0)
    {
        velocityX *= DIAGONAL_SCALE;
        velocityY *= DIAGONAL_SCALE;
    }
}

void Player::takeDamage(double damage)
{
    if (invulnerabilityTimer.isFinished() && isAlive())
    {
        health -= damage;
        invulnerabilityTimer.reset();
    }
}

void Player::handleWeaponActions(std::vector<MouseInputInfo> &actionInput, std::deque<Projectile> &projectiles)
{
    for (size_t i = 0; i < actionInput.size(); ++i)
    {
        if (actionInput[i].active)
        {
            switch (static_cast<MouseInputType>(i))
            {
            case MouseInputType::left:
                item->useAbility1(x, y, actionInput[i].x, actionInput[i].y, colisionRadius, projectiles);
                break;
            case MouseInputType::right:
                item->useAbility2(x, y, actionInput[i].x, actionInput[i].y, colisionRadius, projectiles);
                break;
            case MouseInputType::middle:
                item->useAbility3(x, y, actionInput[i].x, actionInput[i].y, colisionRadius, projectiles);
                break;
            }
        }
    }
}
