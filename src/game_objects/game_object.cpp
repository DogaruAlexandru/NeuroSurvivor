#include "game_objects/game_object.h"
#include "camera.h"

GameObject::GameObject(double x, double y, double scaleVelocityX, double scaleVelocityY, double scaleRadius, double scaleColisionRadius, double scaleMaxSpeed)
    : baseUnit(Camera::getInstance().getBaseUnit()), x(x), y(y), velocityX(scaleVelocityX * baseUnit), velocityY(scaleVelocityY * baseUnit), radius(scaleRadius * baseUnit), colisionRadius(scaleColisionRadius * baseUnit), maxSpeed(scaleMaxSpeed * baseUnit), prevX(x), prevY(y)
{
}

void GameObject::move(double deltaTime)
{
    prevX = x;
    prevY = y;
    x += velocityX * deltaTime;
    y += velocityY * deltaTime;
}

bool GameObject::collidesWith(const GameObject &other) const
{
    double dx = x - other.x;
    double dy = y - other.y;
    double distanceSquared = dx * dx + dy * dy;
    double colisionRadiusSum = colisionRadius + other.colisionRadius;
    return distanceSquared <= colisionRadiusSum * colisionRadiusSum;
}

double GameObject::getX() const { return x; }
double GameObject::getY() const { return y; }
double GameObject::getVelocityX() const { return velocityX; }
double GameObject::getVelocityY() const { return velocityY; }
double GameObject::getRadius() const { return radius; }
double GameObject::getColisionRadius() const { return colisionRadius; }
double GameObject::getMaxSpeed() const { return maxSpeed; }
double GameObject::getPrevX() const { return prevX; }
double GameObject::getPrevY() const { return prevY; }
void GameObject::setRadius(double newRadius) { radius = newRadius; }
void GameObject::setColisionRadius(double newColisionRadius) { colisionRadius = newColisionRadius; }
void GameObject::setMaxSpeed(double newSpeed) { maxSpeed = newSpeed; }

void GameObject::setPosition(double newX, double newY)
{
    prevX = newX;
    prevY = newY;
    x = newX;
    y = newY;
}

void GameObject::setVelocity(double newVelocityX, double newVelocityY)
{
    velocityX = newVelocityX;
    velocityY = newVelocityY;
}