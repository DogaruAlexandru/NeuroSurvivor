#include "game_objects/entity.h"

Entity::Entity(double x, double y, double scaleVelocityX, double scaleVelocityY, double scaleRadius, double scaleColisionRadius, double scaleMaxSpeed, double health, double maxHealth)
    : GameObject(x, y, scaleVelocityX, scaleVelocityY, scaleRadius, scaleColisionRadius, scaleMaxSpeed), health(health), maxHealth(maxHealth)
{
}

bool Entity::isAlive() const
{
    return health > 0;
}

void Entity::takeDamage(double damage)
{
    if (isAlive())
    {
        health -= damage;
    }
}

double Entity::getHealth() const { return health; }
double Entity::getMaxHealth() const { return maxHealth; }
void Entity::setHealth(double newHealth) { health = newHealth; }
void Entity::setMaxHealth(double newMaxHealth) { maxHealth = newMaxHealth; }
