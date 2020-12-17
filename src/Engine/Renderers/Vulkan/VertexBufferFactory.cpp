#include "VertexBufferFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            VertexBufferFactory::VertexBufferFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[]) 
                :   //INITIALIZATION ORDER MATTERS
                    CACHED_DEVICE { device },
                    BUFFER { this->createBuffer(device, deviceSize, queueFamilyIndex, queueFamilyIndices) },
                    MEMORY_REQUIREMENTS { this->createMemoryRequirementsForBuffer(device, this->BUFFER.get()) }
            {
                
            }

            VertexBufferFactory::~VertexBufferFactory()
            {
                vkDestroyBuffer(*this->CACHED_DEVICE, *this->BUFFER, nullptr);
            }

            std::unique_ptr<const VkBuffer> VertexBufferFactory::createBuffer(const VkDevice* device, const VkDeviceSize& deviceSize, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[]) const
            {
                VkBufferCreateInfo bufferInfo{};
                bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
                bufferInfo.pNext = nullptr; 
                bufferInfo.flags = 0;                                   
                bufferInfo.size = deviceSize;
                bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
                bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;                
                bufferInfo.queueFamilyIndexCount = queueFamilyIndex;                 
                bufferInfo.pQueueFamilyIndices = queueFamilyIndices;

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
        }
    }
}