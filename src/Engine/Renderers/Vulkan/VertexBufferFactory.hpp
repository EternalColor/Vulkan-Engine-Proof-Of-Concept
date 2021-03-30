#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include <stdexcept>

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            //Class intended to create a buffer for vertex data 
            class VertexBufferFactory final
            {
                //Read only, no smart pointer required
                private:
                    const VkDevice* CACHED_DEVICE;

                    std::unique_ptr<const VkBuffer> createBuffer(const VkDevice* device, const VkDeviceSize& deviceSize, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[], const VkBufferUsageFlags& usageFlags) const;
                public:
                    //queueFamilyIndices -> can be set to nullptr if sharingMode is not VK_SHARING_MODE_CONCURRENT 
                    VertexBufferFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[], const VkMemoryPropertyFlags& propertyFlags, const VkBufferUsageFlags& usageFlags);
                    ~VertexBufferFactory();

                    //Read-only "getter fields"
                    const VkDeviceSize SIZE;
                    const std::unique_ptr<const VkBuffer> BUFFER;
            };
        }
    }
}