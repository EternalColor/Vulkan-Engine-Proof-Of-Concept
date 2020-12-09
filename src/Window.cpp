#include "Window.hpp"

Window::Window(const uint32_t&& width, const uint32_t&& height, const char* title, const VkInstance* instance, const VkPhysicalDevice* physicalDevice, const uint32_t& queueFamilyIndex) 
    :   //INITIALIZATION ORDER MATTERS
        width { width },
        height { height },
        CACHED_INSTANCE { instance },
        WINDOW { this->createWindow(width, height, title) }, 
        SURFACE { this->createSurface(this->CACHED_INSTANCE, physicalDevice, queueFamilyIndex, this->WINDOW.get()) },
        SURFACE_CAPABILITIES { this->createSurfaceCapabilities(physicalDevice, this->SURFACE.get()) }
{
}

Window::~Window()
{
    vkDestroySurfaceKHR(*this->CACHED_INSTANCE, *this->SURFACE, nullptr);
    glfwTerminate();
}

void Window::PollEvents() const
{
    glfwPollEvents();
}

void Window::RenderOneFrame() const 
{
    //TODO:: Implement
}

std::unique_ptr<GLFWwindow, DestroyGLFWwindow> Window::createWindow(const uint32_t& width, const uint32_t& height, const char* title) const
{
    if(glfwVulkanSupported() != GLFW_TRUE)
    {
        throw std::runtime_error("Vulkan is not supported!"); 
    }
    
    //Disabled GLFW and OpenGL API because we use Vulkan
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    return std::unique_ptr<GLFWwindow, DestroyGLFWwindow> { glfwCreateWindow(width, height, title, nullptr, nullptr), DestroyGLFWwindow()};
}

std::unique_ptr<const VkSurfaceKHR> Window::createSurface(const VkInstance* vkInstance, const VkPhysicalDevice* physicalDevice, const uint32_t& queueFamilyIndex, GLFWwindow* window) const
{
    std::unique_ptr<VkSurfaceKHR> surface { new VkSurfaceKHR(VK_NULL_HANDLE) };
    glfwCreateWindowSurface(*vkInstance, window, nullptr, surface.get());

    this->checkSurfaceSupport(physicalDevice, queueFamilyIndex, surface.get());

    return surface;
}

void Window::checkSurfaceSupport(const VkPhysicalDevice* physicalDevice, const uint32_t& queueFamilyIndex, const VkSurfaceKHR* surface) const
{
    VkBool32 surfaceSupport = VK_FALSE;

    if(vkGetPhysicalDeviceSurfaceSupportKHR(*physicalDevice, queueFamilyIndex, *surface, &surfaceSupport) != VK_SUCCESS)
    {
        throw std::runtime_error("Error while checking surface support!"); 
    }

    if(surfaceSupport != VK_TRUE)
    {
        throw std::runtime_error("Surface is not supported!"); 
    }
}

std::unique_ptr<const VkSurfaceCapabilitiesKHR> Window::createSurfaceCapabilities(const VkPhysicalDevice* physicalDevice, const VkSurfaceKHR* surface) const
{
    std::unique_ptr<VkSurfaceCapabilitiesKHR> surfaceCapabilities = std::make_unique<VkSurfaceCapabilitiesKHR>();
    
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*physicalDevice, *surface, surfaceCapabilities.get());

    return surfaceCapabilities;
}

const bool Window::CloseRequested() const
{
    return glfwWindowShouldClose(this->WINDOW.get());
}

const uint32_t& Window::GetWidth() const
{
    return this->width;
}

const uint32_t& Window::GetHeight() const
{
    return this->height;
}