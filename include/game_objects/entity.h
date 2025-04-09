#pragma once

#include "game_objects/game_object.h"

class Entity : public GameObject
{
public:
    Entity(double x, double y, double scaleVelocityX, double scaleVelocityY, double scaleRadius, double scaleColisionRadius, double scaleMaxSpeed, double health, double maxHealth);

    bool isAlive() const;
    virtual void takeDamage(double damage);

    double getHealth() const;
    double getMaxHealth() const;
    void setHealth(double newHealth);
    void setMaxHealth(double newMaxHealth);

protected:
    double health;
    double maxHealth;
};