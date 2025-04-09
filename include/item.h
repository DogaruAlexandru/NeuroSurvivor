#pragma once

#include "game_objects/projectile.h"
#include "timer.h"

#include <deque>
#include <memory>

class Item
{
public:
    Item();

    void update(double deltaTime);
    virtual void useAbility1(double startX, double startY, double destX, double destY, double entityRadius, std::deque<Projectile> &projectiles);
    virtual void useAbility2(double startX, double startY, double destX, double destY, double entityRadius, std::deque<Projectile> &projectiles);
    virtual void useAbility3(double startX, double startY, double destX, double destY, double entityRadius, std::deque<Projectile> &projectiles);

private:
    const double ABILITY_1_COOLDOWN = 0.5;

    Timer ability1CooldownTimer;
    Timer ability2CooldownTimer;
    Timer ability3CooldownTimer;
};