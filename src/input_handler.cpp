#include "input_handler.h"
#include "camera.h"

#include <SDL3/SDL.h>

void InputHandler::addKeyInput(const SDL_Scancode scancode)
{
    switch (scancode)
    {
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
        moveInput[static_cast<int>(KeyInputType::up)] = true;
        break;
    case SDL_SCANCODE_S:
    case SDL_SCANCODE_DOWN:
        moveInput[static_cast<int>(KeyInputType::down)] = true;
        break;
    case SDL_SCANCODE_A:
    case SDL_SCANCODE_LEFT:
        moveInput[static_cast<int>(KeyInputType::left)] = true;
        break;
    case SDL_SCANCODE_D:
    case SDL_SCANCODE_RIGHT:
        moveInput[static_cast<int>(KeyInputType::right)] = true;
        break;
    }
}

void InputHandler::removeKeyInput(const SDL_Scancode scancode)
{
    switch (scancode)
    {
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
        moveInput[static_cast<int>(KeyInputType::up)] = false;
        break;
    case SDL_SCANCODE_S:
    case SDL_SCANCODE_DOWN:
        moveInput[static_cast<int>(KeyInputType::down)] = false;
        break;
    case SDL_SCANCODE_A:
    case SDL_SCANCODE_LEFT:
        moveInput[static_cast<int>(KeyInputType::left)] = false;
        break;
    case SDL_SCANCODE_D:
    case SDL_SCANCODE_RIGHT:
        moveInput[static_cast<int>(KeyInputType::right)] = false;
        break;
    }
}

void InputHandler::addMouseInput(float x, float y, Uint8 button)
{
    switch (button)
    {
    case SDL_BUTTON_LEFT:
        actionInput[static_cast<int>(MouseInputType::left)] = {true, screenToWorldX(x), screenToWorldY(y)};
        break;
    case SDL_BUTTON_MIDDLE:
        actionInput[static_cast<int>(MouseInputType::middle)] = {true, screenToWorldX(x), screenToWorldY(y)};
        break;
    case SDL_BUTTON_RIGHT:
        actionInput[static_cast<int>(MouseInputType::right)] = {true, screenToWorldX(x), screenToWorldY(y)};
        break;
    }
}

void InputHandler::removeMouseInput(Uint8 button)
{
    switch (button)
    {
    case SDL_BUTTON_LEFT:
        actionInput[static_cast<int>(MouseInputType::left)].active = false;
        break;
    case SDL_BUTTON_MIDDLE:
        actionInput[static_cast<int>(MouseInputType::middle)].active = false;
        break;
    case SDL_BUTTON_RIGHT:
        actionInput[static_cast<int>(MouseInputType::right)].active = false;
        break;
    }
}

void InputHandler::updateMousePosition(float x, float y)
{
    for (auto &action : actionInput)
    {
        if (action.active)
        {
            action.x = screenToWorldX(x);
            action.y = screenToWorldY(y);
        }
    }
}

float InputHandler::screenToWorldY(float y)
{
    return y - Camera::getInstance().getScreenCenterY() + Camera::getInstance().getWorldCenterY();
}

float InputHandler::screenToWorldX(float x)
{
    return x - Camera::getInstance().getScreenCenterX() + Camera::getInstance().getWorldCenterX();
}

std::vector<bool> &InputHandler::getMoveInput()
{
    return moveInput;
}

std::vector<MouseInputInfo> &InputHandler::getActionInput()
{
    return actionInput;
}
