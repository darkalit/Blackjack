#pragma once
#include <functional>

class EventSystem
{
public:
    void Poll() const;

    std::function<void()> OnQuit;
};
