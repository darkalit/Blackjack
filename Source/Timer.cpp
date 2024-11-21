#include "Timer.h"

#include <chrono>
#include <SDL.h>

Timer::Timer()
{
    Reset();
}

void Timer::Reset()
{
    m_Time = std::chrono::high_resolution_clock::now();
}

double Timer::Dt() const
{
    auto dt = static_cast<std::chrono::time_point<std::chrono::high_resolution_clock>>(std::chrono::high_resolution_clock::now() - m_Time);
    return std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(dt.time_since_epoch()).count();
}

uint32_t Timer::GetTick()
{
    return SDL_GetTicks();
}
