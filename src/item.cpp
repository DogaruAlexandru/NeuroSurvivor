#include "item.h"

#include <cmath>

Item::Item()
    : ability1CooldownTimer(ABILITY_1_COOLDOWN),
      ability2CooldownTimer(0),
      ability3CooldownTimer(0)
{
}

void Item::update(double deltaTime)
{
    ability1CooldownTimer.update(deltaTime);
    ability2CooldownTimer.update(deltaTime);
    ability3CooldownTimer.update(deltaTime);
}

void Item::useAbility1(double startX, double startY, double destX, double destY, double entityRadius, std::deque<Projectile> &projectiles)
{
    if (ability1CooldownTimer.isFinished())
    {
        const double PROJECTILE_RADIUS = 0.008;
        const double PROJECTILE_COLISION_RADIUS = PROJECTILE_RADIUS;
        const double PROJECTILE_MAX_SPEED = 0.3;
        const double PROJECTILE_DAMAGE = 1.0;
        const double PROJECTILE_MAX_DISTANCE = 0.5;

        double dx = destX - startX;
        double dy = destY - startY;
        double distance = std::sqrt(dx * dx + dy * dy);
        double dirX = distance > 0 ? dx / distance : 0;
        double dirY = distance > 0 ? dy / distance : 0;
        double x = startX + dirX * (entityRadius + PROJECTILE_RADIUS);
        double y = startY + dirY * (entityRadius + PROJECTILE_RADIUS);
        double velocityX = dirX * PROJECTILE_MAX_SPEED;
        double velocityY = dirY * PROJECTILE_MAX_SPEED;

        projectiles.emplace_back(x, y, velocityX, velocityY, PROJECTILE_RADIUS, PROJECTILE_COLISION_RADIUS, PROJECTILE_MAX_SPEED, PROJECTILE_DAMAGE, PROJECTILE_MAX_DISTANCE);

        ability1CooldownTimer.reset();
    }
}

void Item::useAbility2(double startX, double startY, double destX, double destY, double entityRadius, std::deque<Projectile> &projectiles)
{
}

void Item::useAbility3(double startX, double startY, double destX, double destY, double entityRadius, std::deque<Projectile> &projectiles)
{
}
