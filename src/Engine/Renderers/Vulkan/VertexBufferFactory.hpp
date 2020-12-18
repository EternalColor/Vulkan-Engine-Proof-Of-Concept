#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <stdexcept>

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            class VertexBufferFactory final
            {
                //Read only, no smart pointer required
                private:
                    const VkDevice* CACHED_DEVICE;

                    std::unique_ptr<const VkBuffer> createBuffer(const VkDevice* device, const VkDeviceSize& deviceSize, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[]) const;
                    std::unique_ptr<const VkMemoryRequirements> createMemoryRequirementsForBuffer(const VkDevice* device, const VkBuffer* buffer) const;
                    std::unique_ptr<const VkDeviceMemory> allocateMemory(const VkDevice* device, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryRequirements* memoryRequirements) const;

                    uint32_t findMemoryType(const uint32_t& typeFilter, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryPropertyFlags&& propertieFlags) const;
                public:
                    VertexBufferFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[]);
                    ~VertexBufferFactory();

                    //Read-only "getter fields"
                    const std::unique_ptr<const VkBuffer> BUFFER;
                    const std::unique_ptr<const VkMemoryRequirements> MEMORY_REQUIREMENTS;
                    const std::unique_ptr<const VkDeviceMemory> MEMORY;
            };
        }
    }
}