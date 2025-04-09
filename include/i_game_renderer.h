#pragma once

class IGameRenderer
{
public:
    virtual ~IGameRenderer() = default;

    virtual void render(double alpha, double timeSinceLastRender) = 0;
};