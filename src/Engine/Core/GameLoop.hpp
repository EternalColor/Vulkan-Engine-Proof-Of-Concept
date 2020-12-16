#pragma once

#include <vulkan/vulkan.h>
//TODO: Make it work with generic window and not just vulkan
#include "../Renderers/Vulkan/Window.hpp"

namespace SnowfallEngine
{
    namespace Core
    {
        namespace GameLoop
        {
            void inline Run(const Renderers::VulkanRenderer::Window * window, const VkDevice* device, const VkQueue* queue, const VkSwapchainKHR* swapchain, const VkSemaphore* semaphoreImageAvailable, const VkSemaphore* semaphoreRenderingDone, const uint32_t& commandBufferCount, const VkCommandBuffer commandBuffers[])
            {
                while(!window->CloseRequested())
                {
                    window->PollEvents();
                    window->RenderOneFrame(device, queue, swapchain, semaphoreImageAvailable, semaphoreRenderingDone, commandBufferCount, commandBuffers);
                }

                //Wait until all operation on the device has finished
                vkDeviceWaitIdle(*device);
            }
        };
    }
}