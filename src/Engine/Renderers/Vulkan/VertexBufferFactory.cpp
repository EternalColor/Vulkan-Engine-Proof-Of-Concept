#include "VertexBufferFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            VertexBufferFactory::VertexBufferFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[]) 
                :   //INITIALIZATION ORDER MATTERS
                    CACHED_DEVICE { device },
                    BUFFER { this->createBuffer(device, deviceSize, queueFamilyIndex, queueFamilyIndices) },
                    MEMORY_REQUIREMENTS { this->createMemoryRequirementsForBuffer(device, this->BUFFER.get()) },
                    MEMORY { this->allocateMemory(device, properties, this->MEMORY_REQUIREMENTS.get()) }
            {
                
            }

            VertexBufferFactory::~VertexBufferFactory()
            {
                vkDestroyBuffer(*this->CACHED_DEVICE, *this->BUFFER, nullptr);
                vkFreeMemory(*this->CACHED_DEVICE, *this->MEMORY, nullptr);
            }

            std::unique_ptr<const VkBuffer> VertexBufferFactory::createBuffer(const VkDevice* device, const VkDeviceSize& deviceSize, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[]) const
            {
                const VkBufferCreateInfo bufferInfo = 
                {
                    .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,                                 
                    .size = deviceSize,
                    .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                    .sharingMode = VK_SHARING_MODE_EXCLUSIVE,            
                    .queueFamilyIndexCount = queueFamilyIndex,                 
                    .pQueueFamilyIndices = queueFamilyIndices,
                };

                //Can not use <const VkBuffer> here because vulkan method requires non-const VkBuffer parameter
                std::unique_ptr<VkBuffer> vertexBuffer { new VkBuffer(VK_NULL_HANDLE) };
                if (vkCreateBuffer(*device, &bufferInfo, nullptr, vertexBuffer.get()) != VK_SUCCESS) 
                {
                    throw std::runtime_error("failed to create vertex buffer!");
                }

                return vertexBuffer;
            }

            std::unique_ptr<const VkMemoryRequirements> VertexBufferFactory::createMemoryRequirementsForBuffer(const VkDevice* device, const VkBuffer* buffer) const
            {
                //Can not use <const VkMemoryRequirements> here because vulkan method requires non-const VkMemoryRequirements parameter
                std::unique_ptr<VkMemoryRequirements> memoryRequirements = std::make_unique<VkMemoryRequirements>();

                vkGetBufferMemoryRequirements(*device, *buffer, memoryRequirements.get());

                return memoryRequirements;
            }

            std::unique_ptr<const VkDeviceMemory> VertexBufferFactory::allocateMemory(const VkDevice* device, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryRequirements* memoryRequirements) const
            {
                const VkMemoryAllocateInfo memoryAllocationInfo = 
                {
                    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                    .allocationSize = memoryRequirements->size,
                    .memoryTypeIndex = findMemoryType(memoryRequirements->memoryTypeBits, properties, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
                };

                //Can not use <const VkDeviceMemory> here because vulkan method requires non-const VkDeviceMemory parameter
                std::unique_ptr<VkDeviceMemory> deviceMemory = std::make_unique<VkDeviceMemory>();

                if (vkAllocateMemory(*device, &memoryAllocationInfo, nullptr, deviceMemory.get()) != VK_SUCCESS)
                {
                    throw std::runtime_error("failed to allocate vertex buffer memory!");
                }       

                return deviceMemory;
            }

            uint32_t VertexBufferFactory::findMemoryType(const uint32_t& typeFilter, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryPropertyFlags&& propertieFlags) const
            {
                for (uint32_t i = 0; i < properties->memoryTypeCount; i++) 
                {
                    if (typeFilter & (1 << i) && (properties->memoryTypes[i].propertyFlags & propertieFlags) == propertieFlags) 
                    {
                        return i;
                    }
                }

                throw std::runtime_error("failed to find suitable memory type!");
            }
        }
    }
}