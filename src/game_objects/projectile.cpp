#include "game_objects/projectile.h"

Projectile::Projectile(double x, double y, double scaleVelocityX, double scaleVelocityY, double scaleRadius, double scaleColisionRadius, double scaleMaxSpeed, double damage, double scaleMaxDistance)
    : GameObject(x, y, scaleVelocityX, scaleVelocityY, scaleRadius, scaleColisionRadius, scaleMaxSpeed), damage(damage), maxDistance(scaleMaxDistance * baseUnit), distanceTraveled(0.0), shouldRemove(false)
{
}

void Projectile::move(double deltaTime)
{
    GameObject::move(deltaTime);

    // Update distance traveled
    distanceTraveled += maxSpeed * deltaTime;

    // Check if the projectile has exceeded its maximum distance
    if (distanceTraveled >= maxDistance)
    {
        shouldRemove = true;
    }
}

double Projectile::getDamage() const { return damage; }
double Projectile::getMaxDistance() const { return maxDistance; }
double Projectile::getDistanceTraveled() const { return distanceTraveled; }
bool Projectile::getShouldRemove() const { return shouldRemove; }
void Projectile::setDamage(double newDamage) { damage = newDamage; }
void Projectile::setMaxDistance(double newMaxDistance) { maxDistance = newMaxDistance; }
void Projectile::setDistanceTraveled(double newDistance) { distanceTraveled = newDistance; }
void Projectile::setShouldRemove(bool newShouldRemove) { shouldRemove = newShouldRemove; }