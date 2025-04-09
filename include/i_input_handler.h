#pragma once

#include <vector>

enum class KeyInputType
{
    up,
    down,
    left,
    right,
};

enum class MouseInputType
{
    left,
    middle,
    right,
};

struct MouseInputInfo
{
    bool active = false;
    float x = 0.0f;
    float y = 0.0f;
};

class IInputHandler
{
public:
    virtual ~IInputHandler() = default;

    virtual std::vector<bool> &getMoveInput() = 0;
    virtual std::vector<MouseInputInfo> &getActionInput() = 0;
};