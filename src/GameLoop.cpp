#include "GameLoop.hpp"

GameLoop::GameLoop(const Window* window)
{
    while(!window->CloseRequested())
    {
        window->PollEvents();
        window->RenderOneFrame();
    }
}