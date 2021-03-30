#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            class CommandBufferRecorder
            {
                public:
                    //Intended as static only class so we can have default constructor and destructor
                    CommandBufferRecorder() = default;
                    ~CommandBufferRecorder() = default;
                
                    static void RecordCommandBuffers(const VkCommandBuffer commandBuffers[], const uint32_t& bufferCount, const VkRenderPass* renderPass, const VkFramebuffer framebuffers[], const uint32_t& windowWidth, const uint32_t windowHeight, const VkPipeline* pipeline, const VkViewport viewports[], const VkRect2D scissors[], const VkBuffer* vertexBuffer, const uint32_t& indexCount, const VkBuffer* indexBuffer);
                    static std::unique_ptr<const VkCommandBuffer> CreateAndBeginCommandBuffer(const VkDevice* device, const VkCommandPool* commandPool);
                    //Copy buffer from source to destination
                    static void CopyBuffer(const VkDevice* device, const VkQueue* queue, const VkBuffer* srcBuffer, const VkBuffer* dstBuffer, const VkDeviceSize& size, const VkCommandPool* commandPool);
                    static void TransitionImageLayout(const VkImage* image, const VkFormat* format, const VkImageLayout* oldLayout, const VkImageLayout* newLayout);
 
                

                
                {
                    VkCommandBuffer commandBuffer
                }
            }
        }
    }
}