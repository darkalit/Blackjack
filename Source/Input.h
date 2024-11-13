#pragma once
#include <SDL_keycode.h>
#include <unordered_map>

#include "InputKey.h"

enum class KeyActivation : uint8_t
{
    ON_START,
    HOLD,
    ON_END,
};

class Input
{
public:
    static int GetKeyIsCalled(InputKey key, KeyActivation keyActivation = KeyActivation::HOLD);

private:
    friend class EventSystem;

    struct InputState
    {
        int NewVal;
        int PrevVal;
    };

    static void UpdateKeyboardState(SDL_Keycode key, int32_t value);
    static void UpdateMouseState(uint8_t mouseButton, int32_t value);
    static void UpdateMouseMotion(int32_t x, int32_t y);

    static InputKey SDLKeyToInputKey(SDL_Keycode key);
    static InputKey SDLMouseButtonToInputKey(uint8_t key);

    static std::unordered_map<InputKey, InputState> m_InputValues;
};

