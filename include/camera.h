#pragma once

class Camera
{
public:
    static Camera &getInstance();

    void setScreenSize(int width, int height);
    void setWorldCenter(int x, int y);
    int getScreenWidth() const;
    int getScreenHeight() const;
    int getScreenCenterX() const;
    int getScreenCenterY() const;
    int getWorldCenterX() const;
    int getWorldCenterY() const;
    int getBaseUnit() const;

private:
    Camera() = default;
    Camera(const Camera &) = delete;
    Camera &operator=(const Camera &) = delete;
    ~Camera() = default; // Make destructor private to prevent deletion

    int screenWidth = 0;
    int screenHeight = 0;
    int worldCenterX = 0;
    int worldCenterY = 0;
};