#include <memory>
#include "../../libraries/glfw/include/GLFW/glfw3.h"
#include "GameLoop.hpp"

//Remove and compile as shared library
int main()
{
    glfwInit();
    
    std::make_unique<SnowfallEngine::Core::GameLoop>()->Run();

    glfwTerminate();
    
    return 0;
}

