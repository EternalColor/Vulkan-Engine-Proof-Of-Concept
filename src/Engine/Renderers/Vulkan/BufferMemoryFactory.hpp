#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cstring>
#include "Geometry/Vertex2D.hpp"
#include "../../libraries/stb/stb_image.h"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            class BufferMemoryFactory
            {
                private:    
                    const VkDevice* CACHED_DEVICE;

                    std::unique_ptr<const VkMemoryRequirements> createMemoryRequirementsForBuffer(const VkDevice* device, const VkBuffer* buffer) const;
                    std::unique_ptr<const VkMemoryRequirements> createMemoryRequirementsForBuffer(const VkDevice* device, const VkImage* image) const;
                    std::unique_ptr<const VkDeviceMemory> allocateMemory(const VkDevice* device, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryRequirements* memoryRequirements, const VkMemoryPropertyFlags& propertyFlags) const;
 
                    const uint32_t findMemoryType(const uint32_t& typeFilter, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryPropertyFlags& propertyFlags) const;

                    //Bind either buffer or image (also a kind of buffer) to memory
                    void bindMemory(const VkDevice* device, const VkBuffer* buffer, const VkDeviceMemory* deviceMemory) const;
                    void bindMemory(const VkDevice* device, const VkImage* image, const VkDeviceMemory* deviceMemory) const;

                    //Map Memory methods take either vertices, indices or texel and copies them into VkDeviceMemory
                    void mapMemory(const VkDevice* device, const VkDeviceMemory* deviceMemory, const VkDeviceSize& deviceSize, const std::vector<Geometry::Vertex2D>* vertices) const;
                    void mapMemory(const VkDevice* device, const VkDeviceMemory* deviceMemory, const VkDeviceSize& deviceSize, const std::vector<uint16_t>* indices) const;
                    void mapMemory(const VkDevice* device, const VkDeviceMemory* deviceMemory, const VkDeviceSize& deviceSize, stbi_uc* texel) const;

                    BufferMemoryFactory(const VkDevice* device, const VkPhysicalDeviceMemoryProperties* properties, const VkBuffer* buffer, const VkMemoryPropertyFlags& propertyFlags);
                    BufferMemoryFactory(const VkDevice* device, const VkPhysicalDeviceMemoryProperties* properties, const VkImage* imageBuffer, const VkMemoryPropertyFlags& propertyFlags);
                public:
                    //Constructor for Vertex data
                    BufferMemoryFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryPropertyFlags& propertyFlags, const VkBuffer* buffer, const std::vector<Geometry::Vertex2D>* vertices, const bool&& isStagingBuffer);
                    //Constructor for indices data
                    BufferMemoryFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryPropertyFlags& propertyFlags, const VkBuffer* buffer, const std::vector<uint16_t>* indices, const bool&& isStagingBuffer);
                    //Constructor for texel (image pixel) data
                    BufferMemoryFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryPropertyFlags& propertyFlags, stbi_uc* texel, const VkImage* image, const bool&& isStagingBuffer);
                    ~BufferMemoryFactory();

                    //Read-only "getter fields"
                    const std::unique_ptr<const VkMemoryRequirements> MEMORY_REQUIREMENTS;
                    const std::unique_ptr<const VkDeviceMemory> MEMORY;
            };
        }
    }
}