#include "Renderer.hpp"

//Cant use std::make_unique because were using a VK_NULL_HANDLE
Renderer::Renderer() 
{
  
}

Renderer::~Renderer()
{

}

    //TODO: Move to PhysicalDeviceQueue
  /*  VkQueue queue {};
    vkGetDeviceQueue(*this->device, this->deviceQueueCreateInfo->queueFamilyIndex, 0, &queue); 

    VkFenceCreateInfo fenceCreateInfo {};
    fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceCreateInfo.pNext = nullptr;
    fenceCreateInfo.flags = 0;

    VkFence fence {};
    vkCreateFence(*this->device, &fenceCreateInfo, nullptr, &fence);

    VkSemaphoreCreateInfo semaphoreCreateInfo {};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreCreateInfo.pNext = nullptr;
    semaphoreCreateInfo.flags = 0;

    VkSemaphore semaphore {};
    vkCreateSemaphore(*this->device, &semaphoreCreateInfo, nullptr, &semaphore);

    VkCommandPoolCreateInfo commandPoolCreateInfo {};
    commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolCreateInfo.pNext = nullptr;
    commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    commandPoolCreateInfo.queueFamilyIndex = this->deviceQueueCreateInfo->queueFamilyIndex;

    VkCommandPool commandPool {};
    vkCreateCommandPool(*this->device, &commandPoolCreateInfo, nullptr, &commandPool);

    VkCommandBufferAllocateInfo commandBufferAllocateInfo {};
    commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocateInfo.pNext = nullptr;
    commandBufferAllocateInfo.commandPool = commandPool;
    commandBufferAllocateInfo.commandBufferCount = 1;
    commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    
    VkCommandBuffer commandBuffer {};
    vkAllocateCommandBuffers(*this->device, &commandBufferAllocateInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.pNext = nullptr;
    beginInfo.flags = 0;
    beginInfo.pInheritanceInfo = nullptr;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkViewport viewport {};
    viewport.x = 0;
    viewport.y = 0;
    viewport.width = 512;
    viewport.height = 512;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    vkEndCommandBuffer(commandBuffer);

    VkPipelineStageFlags pipelineStageFlags[1]{ VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT };

    VkSubmitInfo submitInfo {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext = nullptr;
    submitInfo.waitSemaphoreCount = 0;
    submitInfo.pWaitSemaphores = nullptr;
    //Wait until fragment shader has run in the pipeline
    submitInfo.pWaitDstStageMask = pipelineStageFlags;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;
    submitInfo.signalSemaphoreCount = 0;
    submitInfo.pSignalSemaphores = nullptr;

    vkQueueSubmit(queue, 1, &submitInfo, fence);

    if(vkWaitForFences(*this->device, 1, &fence, VK_TRUE, UINT64_MAX)  != VK_SUCCESS)
    {
        throw std::runtime_error("Error waiting for fences");
    };

    vkQueueWaitIdle(queue);

    vkDestroySemaphore(*this->device, semaphore, nullptr);

    vkDestroyFence(*this->device, fence, nullptr);

    vkDestroyCommandPool(*this->device, commandPool, nullptr);*/
