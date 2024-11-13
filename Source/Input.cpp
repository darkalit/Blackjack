#include "Input.h"

#include <SDL_mouse.h>

std::unordered_map<InputKey, Input::InputState> Input::m_InputValues = {};
    
int Input::GetKeyIsCalled(InputKey key, KeyActivation keyActivation)
{
    switch (keyActivation) {
    case KeyActivation::ON_START:
        if (m_InputValues[key].NewVal > m_InputValues[key].PrevVal) {
            m_InputValues[key].PrevVal = m_InputValues[key].NewVal;
            return m_InputValues[key].NewVal;
        }
        return 0;

    case KeyActivation::HOLD:
        return m_InputValues[key].NewVal;

    case KeyActivation::ON_END:
        if (m_InputValues[key].NewVal < m_InputValues[key].PrevVal) {
            int prevVal = m_InputValues[key].PrevVal;
            m_InputValues[key].PrevVal = 0;
            return prevVal;
        }
        return 0;
    }

    return 0;
}

void Input::UpdateKeyboardState(SDL_Keycode key, int32_t value)
{
    InputKey iKey = SDLKeyToInputKey(key);

    m_InputValues[iKey].PrevVal = m_InputValues[iKey].NewVal;
    m_InputValues[iKey].NewVal = value;
}

void Input::UpdateMouseState(uint8_t mouseButton, int32_t value)
{
    InputKey iKey = SDLMouseButtonToInputKey(mouseButton);

    m_InputValues[iKey].PrevVal = m_InputValues[iKey].NewVal;
    m_InputValues[iKey].NewVal = value;
}

void Input::UpdateMouseMotion(int32_t x, int32_t y)
{
    m_InputValues[InputKey::MOUSE_X].PrevVal = m_InputValues[InputKey::MOUSE_X].NewVal;
    m_InputValues[InputKey::MOUSE_Y].PrevVal = m_InputValues[InputKey::MOUSE_Y].NewVal;

    m_InputValues[InputKey::MOUSE_OFFSET_X].NewVal = x - m_InputValues[InputKey::MOUSE_X].PrevVal;
    m_InputValues[InputKey::MOUSE_OFFSET_Y].NewVal = y - m_InputValues[InputKey::MOUSE_Y].PrevVal;

    m_InputValues[InputKey::MOUSE_X].PrevVal = m_InputValues[InputKey::MOUSE_X].NewVal;
    m_InputValues[InputKey::MOUSE_Y].PrevVal = m_InputValues[InputKey::MOUSE_Y].NewVal;
    m_InputValues[InputKey::MOUSE_X].NewVal = x;
    m_InputValues[InputKey::MOUSE_Y].NewVal = y;
}

InputKey Input::SDLKeyToInputKey(SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_SPACE:            return InputKey::KEY_SPACE;
    case SDLK_QUOTE:            return InputKey::KEY_APOSTROPHE;
    case SDLK_COMMA:            return InputKey::KEY_COMMA;
    case SDLK_MINUS:            return InputKey::KEY_MINUS;
    case SDLK_PERIOD:           return InputKey::KEY_PERIOD;
    case SDLK_SLASH:            return InputKey::KEY_SLASH;
    case SDLK_0:                return InputKey::KEY_0;
    case SDLK_1:                return InputKey::KEY_1;
    case SDLK_2:                return InputKey::KEY_2;
    case SDLK_3:                return InputKey::KEY_3;
    case SDLK_4:                return InputKey::KEY_4;
    case SDLK_5:                return InputKey::KEY_5;
    case SDLK_6:                return InputKey::KEY_6;
    case SDLK_7:                return InputKey::KEY_7;
    case SDLK_8:                return InputKey::KEY_8;
    case SDLK_9:                return InputKey::KEY_9;
    case SDLK_SEMICOLON:        return InputKey::KEY_SEMICOLON;
    case SDLK_EQUALS:           return InputKey::KEY_EQUAL;
    case SDLK_a:                return InputKey::KEY_A;
    case SDLK_b:                return InputKey::KEY_B;
    case SDLK_c:                return InputKey::KEY_C;
    case SDLK_d:                return InputKey::KEY_D;
    case SDLK_e:                return InputKey::KEY_E;
    case SDLK_f:                return InputKey::KEY_F;
    case SDLK_g:                return InputKey::KEY_G;
    case SDLK_h:                return InputKey::KEY_H;
    case SDLK_i:                return InputKey::KEY_I;
    case SDLK_j:                return InputKey::KEY_J;
    case SDLK_k:                return InputKey::KEY_K;
    case SDLK_l:                return InputKey::KEY_L;
    case SDLK_m:                return InputKey::KEY_M;
    case SDLK_n:                return InputKey::KEY_N;
    case SDLK_o:                return InputKey::KEY_O;
    case SDLK_p:                return InputKey::KEY_P;
    case SDLK_q:                return InputKey::KEY_Q;
    case SDLK_r:                return InputKey::KEY_R;
    case SDLK_s:                return InputKey::KEY_S;
    case SDLK_t:                return InputKey::KEY_T;
    case SDLK_u:                return InputKey::KEY_U;
    case SDLK_v:                return InputKey::KEY_V;
    case SDLK_w:                return InputKey::KEY_W;
    case SDLK_x:                return InputKey::KEY_X;
    case SDLK_y:                return InputKey::KEY_Y;
    case SDLK_z:                return InputKey::KEY_Z;

    case SDLK_BACKSLASH:        return InputKey::KEY_BACKSLASH;
    case SDLK_LEFTBRACKET:      return InputKey::KEY_LEFT_BRACKET;
    case SDLK_RIGHTBRACKET:     return InputKey::KEY_RIGHT_BRACKET;
    case SDLK_ESCAPE:           return InputKey::KEY_ESCAPE;
    case SDLK_RETURN:           return InputKey::KEY_ENTER;
    case SDLK_TAB:              return InputKey::KEY_TAB;
    case SDLK_BACKSPACE:        return InputKey::KEY_BACKSPACE;
    case SDLK_INSERT:           return InputKey::KEY_INSERT;
    case SDLK_DELETE:           return InputKey::KEY_DELETE;
    case SDLK_RIGHT:            return InputKey::KEY_RIGHT;
    case SDLK_LEFT:             return InputKey::KEY_LEFT;
    case SDLK_DOWN:             return InputKey::KEY_DOWN;
    case SDLK_UP:               return InputKey::KEY_UP;
    case SDLK_PAGEUP:           return InputKey::KEY_PAGE_UP;
    case SDLK_PAGEDOWN:         return InputKey::KEY_PAGE_DOWN;
    case SDLK_HOME:             return InputKey::KEY_HOME;
    case SDLK_END:              return InputKey::KEY_END;
    case SDLK_PRINTSCREEN:      return InputKey::KEY_PRINT_SCREEN;
    case SDLK_PAUSE:            return InputKey::KEY_PAUSE;

    case SDLK_F1:               return InputKey::KEY_F1;
    case SDLK_F2:               return InputKey::KEY_F2;
    case SDLK_F3:               return InputKey::KEY_F3;
    case SDLK_F4:               return InputKey::KEY_F4;
    case SDLK_F5:               return InputKey::KEY_F5;
    case SDLK_F6:               return InputKey::KEY_F6;
    case SDLK_F7:               return InputKey::KEY_F7;
    case SDLK_F8:               return InputKey::KEY_F8;
    case SDLK_F9:               return InputKey::KEY_F9;
    case SDLK_F10:              return InputKey::KEY_F10;
    case SDLK_F11:              return InputKey::KEY_F11;
    case SDLK_F12:              return InputKey::KEY_F12;

    case SDLK_LSHIFT:           return InputKey::KEY_LEFT_SHIFT;
    case SDLK_LCTRL:            return InputKey::KEY_LEFT_CONTROL;
    case SDLK_LALT:             return InputKey::KEY_LEFT_ALT;
    case SDLK_RSHIFT:           return InputKey::KEY_RIGHT_SHIFT;
    case SDLK_RCTRL:            return InputKey::KEY_RIGHT_CONTROL;
    case SDLK_RALT:             return InputKey::KEY_RIGHT_ALT;

    case SDLK_UNKNOWN:
    default:
        return InputKey::UNKNOWN;
    }
}

InputKey Input::SDLMouseButtonToInputKey(uint8_t key)
{
    switch (key)
    {
    case SDL_BUTTON_LEFT:
        return InputKey::MOUSE_LB;
    case SDL_BUTTON_MIDDLE:
        return InputKey::MOUSE_MB;
    case SDL_BUTTON_RIGHT:
        return InputKey::MOUSE_RB;
    case SDL_BUTTON_X1:
        return InputKey::MOUSE_X1B;
    case SDL_BUTTON_X2:
        return InputKey::MOUSE_X2B;
    default:
        return InputKey::UNKNOWN;
    }
}
