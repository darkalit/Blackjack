#include "EventSystem.h"

#include <SDL_events.h>

#include "Input.h"

void EventSystem::Poll() const
{
    SDL_Event e;

    SDL_PollEvent(&e);

    switch (e.type)
    {
    case SDL_KEYDOWN:
        Input::UpdateKeyboardState(e.key.keysym.sym, 1);
        break;
    case SDL_KEYUP:
        Input::UpdateKeyboardState(e.key.keysym.sym, 0);
        break;
    case SDL_MOUSEBUTTONDOWN:
        Input::UpdateMouseState(e.button.button, 1);
        break;
    case SDL_MOUSEBUTTONUP:
        Input::UpdateMouseState(e.button.button, 0);
        break;
    case SDL_MOUSEMOTION:
        Input::UpdateMouseMotion(e.motion.x, e.motion.y);
        break;
    case SDL_QUIT:
        OnQuit();
        break;
    default: break;
    }
}
