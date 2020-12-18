#pragma once

#include <vulkan/vulkan.h>

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            namespace CommandBufferRecorder
            {
                void inline RecordCommandBuffers(const VkCommandBuffer commandBuffers[], const uint32_t& bufferCount, const VkRenderPass* renderPass, const VkFramebuffer framebuffers[], const uint32_t& windowWidth, const uint32_t windowHeight, const VkPipeline* pipeline, const VkViewport viewports[], const VkRect2D scissors[])
                {
                    VkCommandBufferBeginInfo commandBufferBeginInfo = 
                    {
                        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                        .pNext = nullptr,
                        .flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
                        .pInheritanceInfo = nullptr
                    };

                    for(uint32_t i = 0; i < bufferCount; ++i)
                    {
                        vkBeginCommandBuffer(commandBuffers[i], &commandBufferBeginInfo);

                        VkClearValue clearValue = { 0.0f, 0.0f, 0.0f, 1.0f };

                        VkRenderPassBeginInfo beginInfo = 
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

                        vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

                        vkCmdEndRenderPass(commandBuffers[i]);

                        vkEndCommandBuffer(commandBuffers[i]);
                    }
                }
            }
        }
    }
}