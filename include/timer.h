#pragma once

class Timer
{
public:
    Timer(double duration);

    void update(double deltaTime);
    void reset();
    bool isFinished() const;

private:
    double elapsedTime;
    double duration;
};