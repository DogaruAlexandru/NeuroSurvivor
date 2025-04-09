#pragma once

class GameObject
{
protected:
    double baseUnit;
    double x, y;
    double velocityX, velocityY;
    double radius;
    double colisionRadius;
    double maxSpeed;
    double prevX, prevY;

public:
    GameObject(double x, double y, double scaleVelocityX, double scaleVelocityY, double scaleRadius, double scaleColisionRadius, double scaleMaxSpeed);

    virtual void move(double deltaTime);
    bool collidesWith(const GameObject &other) const;

    double getX() const;
    double getY() const;
    double getVelocityX() const;
    double getVelocityY() const;
    double getRadius() const;
    double getColisionRadius() const;
    double getMaxSpeed() const;
    double getPrevX() const;
    double getPrevY() const;
    void setRadius(double newRadius);
    void setColisionRadius(double newColisionRadius);
    void setMaxSpeed(double newSpeed);
    void setPosition(double newX, double newY);
    void setVelocity(double newVelocityX, double newVelocityY);
};