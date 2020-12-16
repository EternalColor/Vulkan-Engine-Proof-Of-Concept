#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <stdexcept>
#include "CommandBufferRecorder.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            class CommandBufferFactory final
            {
                private:
                    //Read only, no smart pointer required
                    const VkDevice* CACHED_DEVICE;

                    std::unique_ptr<const VkCommandPool> createCommandPool(const VkDevice* device, const uint32_t& queueFamilyIndex) const;
                    std::unique_ptr<const VkCommandBuffer[]> createCommandBuffers(const VkDevice* device, const VkCommandPool* commandPool, const uint32_t& bufferCount) const;
                public:
                    CommandBufferFactory(const VkDevice* device, const uint32_t& queueFamilyIndex, const uint32_t& bufferCount);
                    ~CommandBufferFactory();

                    //Read-only "getter fields"
                    const uint32_t BUFFER_COUNT;
                    const std::unique_ptr<const VkCommandPool> POOL;
                    const std::unique_ptr<const VkCommandBuffer[]> BUFFERS;
            };
        }
    }
}