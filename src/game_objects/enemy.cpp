#include "game_objects/enemy.h"
#include "camera.h"

#include <random>

Enemy::Enemy(double x, double y, double scaleVelocityX, double scaleVelocityY, double scaleRadius, double scaleColisionRadius, double scaleMaxSpeed, double health, double maxHealth, double meeleDamage, Item *item)
    : Entity(x, y, scaleVelocityX, scaleVelocityY, scaleRadius, scaleColisionRadius, scaleMaxSpeed, health, maxHealth), meeleDamage(meeleDamage), item(item), screenWidth(Camera::getInstance().getScreenWidth()), screenHeight(Camera::getInstance().getScreenHeight())
{
    updateCameraCenters();
}

Enemy::Enemy()
    : Enemy(0.0, 0.0, 0.0, 0.0, RADIUS, COLISION_RADIUS, MAX_SPEED, HEALTH, MAX_HEALTH, MELEE_DAMAGE, nullptr)
{
    setOutsidePos();
}

void Enemy::setOutsidePos()
{
    updateCameraCenters();
    double offset = radius * 4;

    // Ensure enemies are placed outside the player's camera
    if (rand() % 2 == 0)
    {
        // Place enemy horizontally outside the camera
        x = (rand() % 2 == 0) ? worldCenterX - screenCenterX - offset : worldCenterX + screenCenterX + offset;
        y = worldCenterY + (rand() % screenHeight) - screenCenterY;
    }
    else
    {
        // Place enemy vertically outside the camera
        x = worldCenterX + (rand() % screenWidth) - screenCenterX;
        y = (rand() % 2 == 0) ? worldCenterY - screenCenterY - offset : worldCenterY + screenCenterY + offset;
    }

    prevX = x;
    prevY = y;
}

double Enemy::getMeleeDamage()
{
    return meeleDamage;
}

void Enemy::setMeleeDamage(double damage)
{
    meeleDamage = damage;
}

void Enemy::updateCameraCenters()
{
    screenCenterX = Camera::getInstance().getScreenCenterX();
    screenCenterY = Camera::getInstance().getScreenCenterY();
    worldCenterX = Camera::getInstance().getWorldCenterX();
    worldCenterY = Camera::getInstance().getWorldCenterY();
}