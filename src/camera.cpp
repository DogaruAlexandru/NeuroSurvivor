#include "camera.h"

Camera &Camera::getInstance()
{
    static Camera instance; // Thread-safe initialization in C++11 and later
    return instance;
}

void Camera::setScreenSize(int width, int height)
{
    screenWidth = width;
    screenHeight = height;
}

void Camera::setWorldCenter(int x, int y)
{
    worldCenterX = x;
    worldCenterY = y;
}

int Camera::getScreenWidth() const
{
    return screenWidth;
}

int Camera::getScreenHeight() const
{
    return screenHeight;
}

int Camera::getScreenCenterX() const
{
    return screenWidth / 2;
}

int Camera::getScreenCenterY() const
{
    return screenHeight / 2;
}

int Camera::getWorldCenterX() const
{
    return worldCenterX;
}

int Camera::getWorldCenterY() const
{
    return worldCenterY;
}

int Camera::getBaseUnit() const
{
    return screenWidth < screenHeight ? screenWidth : screenHeight;
}
