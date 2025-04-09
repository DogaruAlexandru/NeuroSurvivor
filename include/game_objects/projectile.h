#pragma once

#include "game_objects/game_object.h"

class Projectile : public GameObject
{
public:
    Projectile(double x, double y, double scaleVelocityX, double scaleVelocityY, double scaleRadius, double scaleColisionRadius, double scaleMaxSpeed, double damage, double scaleMaxDistance);

    void move(double deltaTime) override;

    double getDamage() const;
    double getMaxDistance() const;
    double getDistanceTraveled() const;
    bool getShouldRemove() const;
    void setDamage(double newDamage);
    void setMaxDistance(double newMaxDistance);
    void setDistanceTraveled(double newDistance);
    void setShouldRemove(bool newShouldRemove);

private:
    double damage;
    double maxDistance;
    double distanceTraveled;
    bool shouldRemove;
};