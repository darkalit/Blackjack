#pragma once
#include <chrono>
#include <cstdint>

class Timer
{
public:
    Timer();
    void Reset();
    double Dt() const;
    static uint32_t GetTick();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_Time = {};
};

