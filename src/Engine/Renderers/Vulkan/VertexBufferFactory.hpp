#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <stdexcept>
#include <cstring>
#include <vector>
#include "Geometry/Vertex2D.hpp"

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

                    std::unique_ptr<const VkBuffer> createBuffer(const VkDevice* device, const VkDeviceSize& deviceSize, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[], const VkBufferUsageFlags& usageFlags) const;
                    std::unique_ptr<const VkMemoryRequirements> createMemoryRequirementsForBuffer(const VkDevice* device, const VkBuffer* buffer) const;
                    std::unique_ptr<const VkDeviceMemory> allocateMemory(const VkDevice* device, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryRequirements* memoryRequirements, const VkMemoryPropertyFlags& propertyFlags) const;
                    
                    void bindMemory(const VkDevice* device, const VkBuffer* buffer, const VkDeviceMemory* memory) const;
                    void mapMemory(const VkDevice* device, const VkDeviceMemory* deviceMemory, const VkDeviceSize& deviceSize, const std::vector<Geometry::Vertex2D>* vertices) const;
                    void mapMemory(const VkDevice* device, const VkDeviceMemory* deviceMemory, const VkDeviceSize& deviceSize, const std::vector<uint16_t>* indices) const;

                    const uint32_t findMemoryType(const uint32_t& typeFilter, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryPropertyFlags& propertyFlags) const;
                public:
                    //queueFamilyIndices -> can be set to nullptr if sharingMode is not VK_SHARING_MODE_CONCURRENT 
                    //Constructor version intended for the cpu staging vertex buffer, vertices passed here will be copied
                    VertexBufferFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[], const VkMemoryPropertyFlags& propertyFlags, const VkBufferUsageFlags& usageFlags, const std::vector<Geometry::Vertex2D>* vertices, const bool&& isStagingBuffer);
                    VertexBufferFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[], const VkMemoryPropertyFlags& propertyFlags, const VkBufferUsageFlags& usageFlags, const std::vector<uint16_t>* indices);
                    //Constructor version intended for GPU vertex buffer, without vertices (they are copied into the buffer memory, but we already to that previously in a staging vertex buffer)
                    VertexBufferFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[], const VkMemoryPropertyFlags& propertyFlags, const VkBufferUsageFlags& usageFlags);
                    ~VertexBufferFactory();

                    //Read-only "getter fields"
                    const VkDeviceSize DEVICE_SIZE;
                    const std::unique_ptr<const VkBuffer> BUFFER;
                    const std::unique_ptr<const VkMemoryRequirements> MEMORY_REQUIREMENTS;
                    const std::unique_ptr<const VkDeviceMemory> MEMORY;
            };
        }
    }
}