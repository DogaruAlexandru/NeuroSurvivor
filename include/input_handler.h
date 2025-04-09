#pragma once

#include "i_input_handler.h"

#include <SDL3/SDL.h>

class InputHandler : public IInputHandler
{
private:
    std::vector<bool> moveInput = std::vector<bool>(4);
    std::vector<MouseInputInfo> actionInput = std::vector<MouseInputInfo>(3);

    float screenToWorldY(float y);
    float screenToWorldX(float x);

public:
    ~InputHandler() override = default;

    void addKeyInput(const SDL_Scancode scancode);
    void removeKeyInput(const SDL_Scancode scancode);
    void addMouseInput(float x, float y, Uint8 button);
    void removeMouseInput(Uint8 button);
    void updateMousePosition(float x, float y);

    std::vector<bool> &getMoveInput() override;
    std::vector<MouseInputInfo> &getActionInput() override;
};
