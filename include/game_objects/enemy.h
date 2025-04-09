#pragma once

#include "game_objects/entity.h"
#include "item.h"

class Enemy : public Entity
{
public:
    Enemy(double x, double y, double scaleVelocityX, double scaleVelocityY, double scaleRadius, double scaleColisionRadius, double scaleMaxSpeed, double health, double maxHealth, double meeleDamage, Item *item);
    Enemy();

    void setOutsidePos();

    double getMeleeDamage();
    void setMeleeDamage(double damage);

private:
    static constexpr double RADIUS = 0.02;
    static constexpr double COLISION_RADIUS = RADIUS;
    static constexpr double MAX_SPEED = 0.1;
    static constexpr double HEALTH = 2.0;
    static constexpr double MAX_HEALTH = 2.0;
    static constexpr double MELEE_DAMAGE = 1.0;

    double meeleDamage;
    Item *item;

    double screenCenterX;
    double screenCenterY;
    double worldCenterX;
    double worldCenterY;
    int screenWidth;
    int screenHeight;

    void updateCameraCenters();

    // void moveTowards(Entity &target);
};