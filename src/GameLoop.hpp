#pragma once

#include <vulkan/vulkan.h>
#include "Window.hpp"

namespace GameLoop
{
    void inline Run(const Window* window, const VkDevice* device, const VkQueue* queue, const VkSwapchainKHR* swapchain, const VkSemaphore* semaphoreImageAvailable, const VkSemaphore* semaphoreRenderingDone, const uint32_t& commandBufferCount, const VkCommandBuffer commandBuffers[])
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