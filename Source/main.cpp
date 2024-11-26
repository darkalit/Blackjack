#include <iostream>
#include <SDL.h>

#include "Game.h"

int main(int argc, char* argv[])
{
    try {
        Game game(1280, 720);
        game.Launch();
    } catch (std::exception& e)
    {
        std::cout << e.what();
    }

    return 0;
}