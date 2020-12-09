#include <memory>
#include <GLFW/glfw3.h>
#include "Renderer.hpp"
#include "Window.hpp"
#include "GameLoop.hpp"
#include "Runtime.hpp"

//Remove and compile as shared library
int main()
{
    glfwInit();
    
    std::unique_ptr<Runtime> runtime = std::make_unique<Runtime>();
}