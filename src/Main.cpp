#include <memory>
#include <GLFW/glfw3.h>
#include "Renderer.hpp"
#include "Window.hpp"
#include "GameLoop.hpp"
#include "VulkanWrapper.hpp"

//Remove and compile as shared library
int main()
{
    glfwInit();
    
    std::make_unique<VulkanWrapper>();
}