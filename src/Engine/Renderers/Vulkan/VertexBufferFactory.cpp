#include "VertexBufferFactory.hpp"

#include "../../libraries/stb/stb_image.h"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            VertexBufferFactory::VertexBufferFactory(const VkDevice* device, const VkDeviceSize& size, const VkPhysicalDeviceMemoryProperties* properties, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[], const VkMemoryPropertyFlags& propertyFlags, const VkBufferUsageFlags& usageFlags)
             :   //INITIALIZATION ORDER MATTERS
                CACHED_DEVICE { device },
                SIZE { size },
                BUFFER { this->createBuffer(this->CACHED_DEVICE, size, queueFamilyIndex, queueFamilyIndices, usageFlags) }
            {
            }

            VertexBufferFactory::~VertexBufferFactory()
            {
                vkDestroyBuffer(*this->CACHED_DEVICE, *this->BUFFER, nullptr);
            }

            std::unique_ptr<const VkBuffer> VertexBufferFactory::createBuffer(const VkDevice* device, const VkDeviceSize& deviceSize, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[], const VkBufferUsageFlags& usageFlags) const
            {
                const VkBufferCreateInfo bufferInfo
                {
                    .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,                                 
                    .size = deviceSize,
                    .usage = usageFlags,
                    .sharingMode = VK_SHARING_MODE_EXCLUSIVE,            
                    .queueFamilyIndexCount = queueFamilyIndex, //TODO: OOOPS PLS REMOVE THIS, does not mean what i thought
                    .pQueueFamilyIndices = queueFamilyIndices //can be set to nullptr if sharingMode is not VK_SHARING_MODE_CONCURRENT 
                };

                //Can not use <const VkBuffer> here because vulkan method requires non-const VkBuffer parameter
                std::unique_ptr<VkBuffer> vertexBuffer { new VkBuffer(VK_NULL_HANDLE) };
                if (vkCreateBuffer(*device, &bufferInfo, nullptr, vertexBuffer.get()) != VK_SUCCESS) 
                {
                    throw std::runtime_error("failed to create vertex buffer!");
                }

                return vertexBuffer;
            }

         
        }
    }
}