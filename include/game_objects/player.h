#pragma once

#include "game_objects/entity.h"
#include "timer.h"
#include "game_objects/projectile.h"
#include "input_handler.h"
#include "item.h"

#include <deque>
#include <memory>

class Player : public Entity
{
public:
    Player(double x, double y, double scaleVelocityX, double scaleVelocityY, double scaleRadius, double scaleColisionRadius, double scaleMaxSpeed, double health, double maxHealth);
    Player(double x, double y);

    void update(double deltaTime, std::vector<bool> &moveInput, std::vector<MouseInputInfo> &actionInput, std::deque<Projectile> &projectiles);
    void takeDamage(double damage) override;

private:
    static constexpr double DIAGONAL_SCALE = 0.7071;
    static constexpr double RADIUS = 0.1;
    static constexpr double COLISION_RADIUS = RADIUS * 0.2;
    static constexpr double MAX_SPEED = 0.2;
    static constexpr double HEALTH = 5.0;
    static constexpr double MAX_HEALTH = 5.0;
    static constexpr double INVULNERABILITY_TIME = 0.5;

    void setVelocity(std::vector<bool> &moveInput);
    void handleWeaponActions(std::vector<MouseInputInfo> &actionInput, std::deque<Projectile> &projectiles);

    std::shared_ptr<Item> item;
    Timer invulnerabilityTimer;
};