#include <memory>
#include <GLFW/glfw3.h>
#include "../Renderers/Vulkan/VulkanWrapper.hpp"

//Remove and compile as shared library

int main()
{
    glfwInit();
    
    std::make_unique<SnowfallEngine::Renderers::VulkanRenderer::VulkanWrapper>();

    glfwTerminate();
    
    return 0;
}

