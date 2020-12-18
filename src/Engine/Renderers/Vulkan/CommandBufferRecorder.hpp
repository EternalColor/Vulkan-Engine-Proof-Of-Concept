#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            namespace CommandBufferRecorder
            {
                void inline RecordCommandBuffers(const VkCommandBuffer commandBuffers[], const uint32_t& bufferCount, const VkRenderPass* renderPass, const VkFramebuffer framebuffers[], const uint32_t& windowWidth, const uint32_t windowHeight, const VkPipeline* pipeline, const VkViewport viewports[], const VkRect2D scissors[], const uint32_t& vertexCount, const VkBuffer* vertexBuffer)
                {
                    const VkCommandBufferBeginInfo commandBufferBeginInfo
                    {
                        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                        .pNext = nullptr,
                        .flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
                        .pInheritanceInfo = nullptr
                    };

                    for(uint32_t i = 0; i < bufferCount; ++i)
                    {
                        vkBeginCommandBuffer(commandBuffers[i], &commandBufferBeginInfo);

                        const VkClearValue clearValue = { 0.0f, 0.0f, 0.0f, 1.0f };

                        const VkRenderPassBeginInfo beginInfo 
                        {
                            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
                            .pNext = nullptr,
                            .renderPass = *renderPass,
                            .framebuffer = framebuffers[i],
                            .renderArea = 
                            {
                                .offset = { 0, 0 },
                                .extent = { windowWidth, windowHeight }
                            },
                            .clearValueCount = 1,
                            .pClearValues = &clearValue
                        };

                        vkCmdBeginRenderPass(commandBuffers[i], &beginInfo, VK_SUBPASS_CONTENTS_INLINE);

                        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, *pipeline);

                        vkCmdSetViewport(commandBuffers[i], 0, 1, viewports);

                        vkCmdSetScissor(commandBuffers[i], 0, 1, scissors);

                        VkDeviceSize offsets[] = {0};

                        vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffer, offsets);

                        vkCmdDraw(commandBuffers[i], vertexCount, 1, 0, 0);

                        vkCmdEndRenderPass(commandBuffers[i]);

                        vkEndCommandBuffer(commandBuffers[i]);
                    }
                }

                void inline CopyBuffer(const VkDevice* device, const VkQueue* queue, const VkBuffer* srcBuffer, const VkBuffer* dstBuffer, const VkDeviceSize& size, const VkCommandPool* commandPool)
                {
                    const VkCommandBufferAllocateInfo allocInfo
                    {
                        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
                        .commandPool = *commandPool,
                        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
                        .commandBufferCount = 1
                    };

                    const VkCommandBufferBeginInfo beginInfo
                    {
                        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
                    };

                    VkCommandBuffer commandBuffer { VK_NULL_HANDLE };

                    //Record copy command buffer
                    vkAllocateCommandBuffers(*device, &allocInfo, &commandBuffer);
                    vkBeginCommandBuffer(commandBuffer, &beginInfo);

                    const VkBufferCopy copyRegion
                    {
                        .srcOffset = 0, // Optional
                        .dstOffset = 0, // Optional
                        .size = size
                    };

                    vkCmdCopyBuffer(commandBuffer, *srcBuffer, *dstBuffer, 1, &copyRegion);
                    vkEndCommandBuffer(commandBuffer);
        
                    VkSubmitInfo submitInfo{};
                    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
                    submitInfo.commandBufferCount = 1;
                    submitInfo.pCommandBuffers = &commandBuffer;

                    vkQueueSubmit(*queue, 1, &submitInfo, VK_NULL_HANDLE);
                    vkQueueWaitIdle(*queue);

                    vkFreeCommandBuffers(*device, *commandPool, 1, &commandBuffer);
                }
            }
        }
    }
}