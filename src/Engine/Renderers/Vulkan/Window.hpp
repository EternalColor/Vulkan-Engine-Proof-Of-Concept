#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <memory>
#include <limits>
#include <stdexcept>


namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            //Delete struct for GLFWwindow -> so we can use unique_ptr<GLFWwindow, DestroyGLFWwindow>
            //Still requires glfwTerminate() to be executed from elsewhere! -> In Window destructor glfwTerminate() is called
            struct DestroyGLFWwindow final
            {
                void operator()(GLFWwindow* ptr)
                {
                    glfwDestroyWindow(ptr);
                }
            };

            class Window final
            {
                private:
                    uint32_t width;
                    uint32_t height;

                    //Read only, no smart pointer required
                    const VkInstance* CACHED_INSTANCE;

                    std::unique_ptr<GLFWwindow, DestroyGLFWwindow> createWindow(const uint32_t& width, const uint32_t& height, const char* title) const;

                    void checkSurfaceSupport(const VkPhysicalDevice* physicalDevice, const uint32_t& queueFamilyIndex, const VkSurfaceKHR* surface) const;

                    std::unique_ptr<const VkSurfaceKHR> createSurface(const VkInstance* vkInstance, const VkPhysicalDevice* physicalDevice, const uint32_t& queueFamilyIndex, GLFWwindow* window) const;
                    std::unique_ptr<const VkSurfaceCapabilitiesKHR> createSurfaceCapabilities(const VkPhysicalDevice* physicalDevice, const VkSurfaceKHR* surface) const;
                    std::unique_ptr<const VkSurfaceFormatKHR[]> getSurfaceFormats(const VkPhysicalDevice* physicalDevice, const VkSurfaceKHR* surface) const;
                public:
                    //Read-only "getter fields"
                    const std::unique_ptr<GLFWwindow, DestroyGLFWwindow> WINDOW;
                    const std::unique_ptr<const VkSurfaceKHR> SURFACE;
                    const std::unique_ptr<const VkSurfaceCapabilitiesKHR> SURFACE_CAPABILITIES;
                    const std::unique_ptr<const VkSurfaceFormatKHR[]> SURFACE_FORMATS;

                    Window(const uint32_t&& width, const uint32_t&& height, const char* title, const VkInstance* instance, const VkPhysicalDevice* physicalDevice, const uint32_t& queueFamilyIndex);
                    ~Window(); 

                    void PollEvents() const;
                    void RenderOneFrame(const VkDevice* device, const VkQueue* queue, const VkSwapchainKHR* swapchain, const VkSemaphore* semaphoreImageAvailable, const VkSemaphore* semaphoreRenderingDone, const uint32_t& commandBufferCount, const VkCommandBuffer commandBuffers[]) const;
                    const bool CloseRequested() const;

                    const uint32_t& GetWidth() const;
                    const uint32_t& GetHeight() const;
            };
        }
    }
}