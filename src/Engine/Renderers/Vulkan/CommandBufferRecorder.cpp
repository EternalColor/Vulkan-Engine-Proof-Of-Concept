#include "CommandBufferRecorder.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            void CommandBufferRecorder::RecordCommandBuffers(const VkCommandBuffer commandBuffers[], const uint32_t& bufferCount, const VkRenderPass* renderPass, const VkFramebuffer framebuffers[], const uint32_t& windowWidth, const uint32_t windowHeight, const VkPipeline* pipeline, const VkViewport viewports[], const VkRect2D scissors[], const VkBuffer* vertexBuffer, const uint32_t& indexCount, const VkBuffer* indexBuffer)
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

                    vkCmdBindIndexBuffer(commandBuffers[i], *indexBuffer, 0, VK_INDEX_TYPE_UINT16);

                    vkCmdDrawIndexed(commandBuffers[i], indexCount, 1, 0, 0, 0);

                    vkCmdEndRenderPass(commandBuffers[i]);

                    vkEndCommandBuffer(commandBuffers[i]);
                }
            }

            std::unique_ptr<const VkCommandBuffer> CommandBufferRecorder::CreateAndBeginCommandBuffer(const VkDevice* device, const VkCommandPool* commandPool)
            {
                const VkCommandBufferAllocateInfo allocInfo
                {
                    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
                    .pNext = nullptr,
                    .commandPool = *commandPool,
                    .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
                    .commandBufferCount = 1
                };

                const VkCommandBufferBeginInfo beginInfo
                {
                    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                    .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
                };

                //Can not use <const VkCommandBuffer> here because vulkan method requires non-const VkCommandBuffer parameter
                std::unique_ptr<VkCommandBuffer> commandBuffer { new VkCommandBuffer(VK_NULL_HANDLE) };

                //Record copy command buffer
                vkAllocateCommandBuffers(*device, &allocInfo, commandBuffer.get());
                vkBeginCommandBuffer(*commandBuffer, &beginInfo);

                return commandBuffer;
            }

            void CommandBufferRecorder::CopyBuffer(const VkDevice* device, const VkQueue* queue, const VkBuffer* srcBuffer, const VkBuffer* dstBuffer, const VkDeviceSize& size, const VkCommandPool* commandPool)
            {
                const VkBufferCopy copyRegion
                {
                    .srcOffset = 0, // Optional
                    .dstOffset = 0, // Optional
                    .size = size
                };

                vkCmdCopyBuffer(commandBuffer, *srcBuffer, *dstBuffer, 1, &copyRegion);
                vkEndCommandBuffer(commandBuffer);
    
                const VkSubmitInfo submitInfo
                {
                    .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                    .commandBufferCount = 1,
                    .pCommandBuffers = &commandBuffer
                };

                vkQueueSubmit(*queue, 1, &submitInfo, VK_NULL_HANDLE);
                vkQueueWaitIdle(*queue);

                vkFreeCommandBuffers(*device, *commandPool, 1, &commandBuffer);
            }

            void CommandBufferRecorder::TransitionImageLayout(const VkImage* image, const VkFormat* format, const VkImageLayout* oldLayout, const VkImageLayout* newLayout)
            {
                VkCommandBuffer commandBuffer
                
            }
        }
    }
}