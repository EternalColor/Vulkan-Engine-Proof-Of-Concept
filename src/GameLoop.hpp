#pragma once

#include "Window.hpp"

class GameLoop final
{
    public:
        GameLoop(const Window* window);
        ~GameLoop() = default;
};