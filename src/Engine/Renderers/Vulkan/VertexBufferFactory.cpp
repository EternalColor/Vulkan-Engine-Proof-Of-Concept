#include "VertexBufferFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            VertexBufferFactory::VertexBufferFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[], const VkMemoryPropertyFlags& propertyFlags, const VkBufferUsageFlags& usageFlags)
             :   //INITIALIZATION ORDER MATTERS
                CACHED_DEVICE { device },
                DEVICE_SIZE { deviceSize },
                BUFFER { this->createBuffer(this->CACHED_DEVICE, deviceSize, queueFamilyIndex, queueFamilyIndices, usageFlags) },
                MEMORY_REQUIREMENTS { this->createMemoryRequirementsForBuffer(this->CACHED_DEVICE, this->BUFFER.get()) },
                MEMORY { this->allocateMemory(this->CACHED_DEVICE, properties, this->MEMORY_REQUIREMENTS.get(), propertyFlags) }
            {
            }
            
            //Constructor for Vertex Buffer
            VertexBufferFactory::VertexBufferFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[], const VkMemoryPropertyFlags& propertyFlags, const VkBufferUsageFlags& usageFlags, const std::vector<Geometry::Vertex2D>* vertices, const bool&& isStagingBuffer) 
               : VertexBufferFactory(device, deviceSize, properties, queueFamilyIndex, queueFamilyIndices, propertyFlags, usageFlags)
            {
                if(isStagingBuffer)
                {
                    this->mapMemory(this->CACHED_DEVICE, this->MEMORY.get(), deviceSize, vertices);
                }

                this->bindMemory(this->CACHED_DEVICE, this->BUFFER.get(), this->MEMORY.get());
            }

            //Constructor for Index buffer
            VertexBufferFactory::VertexBufferFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[], const VkMemoryPropertyFlags& propertyFlags, const VkBufferUsageFlags& usageFlags, const std::vector<uint16_t>* indices, const bool&& isStagingBuffer)
                : VertexBufferFactory(device, deviceSize, properties, queueFamilyIndex, queueFamilyIndices, propertyFlags, usageFlags)
            {
                if(isStagingBuffer)
                {
                    this->mapMemory(this->CACHED_DEVICE, this->MEMORY.get(), deviceSize, indices);
                }

                this->bindMemory(this->CACHED_DEVICE, this->BUFFER.get(), this->MEMORY.get());
            }

            //Constructor for Texel (TextureImage pixels) Buffer
            VertexBufferFactory::VertexBufferFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const uint32_t& queueFamilyIndex, const uint32_t queueFamilyIndices[], const VkMemoryPropertyFlags& propertyFlags, const VkBufferUsageFlags& usageFlags, stbi_uc* texel, const bool&& isStagingBuffer)
                : VertexBufferFactory(device, deviceSize, properties, queueFamilyIndex, queueFamilyIndices, propertyFlags, usageFlags)
            {
                if(isStagingBuffer)
                {
                    this->mapMemory(this->CACHED_DEVICE, this->MEMORY.get(), deviceSize, texel);
                }

                this->bindMemory(this->CACHED_DEVICE, this->BUFFER.get(), this->MEMORY.get());
            }

            VertexBufferFactory::~VertexBufferFactory()
            {
                vkDestroyBuffer(*this->CACHED_DEVICE, *this->BUFFER, nullptr);
                vkFreeMemory(*this->CACHED_DEVICE, *this->MEMORY, nullptr);
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
                    .queueFamilyIndexCount = queueFamilyIndex,                 
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

            std::unique_ptr<const VkMemoryRequirements> VertexBufferFactory::createMemoryRequirementsForBuffer(const VkDevice* device, const VkBuffer* buffer) const
            {
                //Can not use <const VkMemoryRequirements> here because vulkan method requires non-const VkMemoryRequirements parameter
                std::unique_ptr<VkMemoryRequirements> memoryRequirements = std::make_unique<VkMemoryRequirements>();

                vkGetBufferMemoryRequirements(*device, *buffer, memoryRequirements.get());

                return memoryRequirements;
            }

            std::unique_ptr<const VkDeviceMemory> VertexBufferFactory::allocateMemory(const VkDevice* device, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryRequirements* memoryRequirements, const VkMemoryPropertyFlags& propertyFlags) const
            {
                const VkMemoryAllocateInfo memoryAllocationInfo = 
                {
                    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                    .allocationSize = memoryRequirements->size,
                    .memoryTypeIndex = findMemoryType(memoryRequirements->memoryTypeBits, properties, propertyFlags) 
                    //findMemoryType flags explained-> Must be visible to the CPU (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT bit specifies that the host cache management commands 
                };

                //Can not use <const VkDeviceMemory> here because vulkan method requires non-const VkDeviceMemory parameter
                std::unique_ptr<VkDeviceMemory> deviceMemory = std::make_unique<VkDeviceMemory>();

                if (vkAllocateMemory(*device, &memoryAllocationInfo, nullptr, deviceMemory.get()) != VK_SUCCESS)
                {
                    throw std::runtime_error("failed to allocate vertex buffer memory!");
                }      

                return deviceMemory;
            }

            void VertexBufferFactory::bindMemory(const VkDevice* device, const VkBuffer* buffer, const VkDeviceMemory* memory) const
            {
                vkBindBufferMemory(*device, *buffer, *memory, 0);
            }

            void VertexBufferFactory::mapMemory(const VkDevice* device, const VkDeviceMemory* deviceMemory, const VkDeviceSize& deviceSize, const std::vector<Geometry::Vertex2D>* vertices) const
            {
                void* data;
                vkMapMemory(*device, *deviceMemory, 0, deviceSize, 0, &data);
                
                //Copy vertices into data
                std::memcpy(data, vertices->data(), static_cast<size_t>(deviceSize));

                vkUnmapMemory(*device, *deviceMemory);
            }

            void VertexBufferFactory::mapMemory(const VkDevice* device, const VkDeviceMemory* deviceMemory, const VkDeviceSize& deviceSize, const std::vector<uint16_t>* indices) const
            {
                void* data;
                vkMapMemory(*device, *deviceMemory, 0, deviceSize, 0, &data);
                
                //Copy vertices into data
                std::memcpy(data, indices->data(), static_cast<size_t>(deviceSize));

                vkUnmapMemory(*device, *deviceMemory);
            }

            void VertexBufferFactory::mapMemory(const VkDevice* device, const VkDeviceMemory* deviceMemory, const VkDeviceSize& deviceSize, stbi_uc* texel) const
            {
                void* data;
                vkMapMemory(*device, *deviceMemory, 0, deviceSize, 0, &data);
                
                //Copy vertices into data
                std::memcpy(data, texel, static_cast<size_t>(deviceSize));

                vkUnmapMemory(*device, *deviceMemory);
            }

            const uint32_t VertexBufferFactory::findMemoryType(const uint32_t& typeFilter, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryPropertyFlags& propertyFlags) const
            {
                for (uint32_t i = 0; i < properties->memoryTypeCount; i++) 
                {
                    if (typeFilter & (1 << i) && (properties->memoryTypes[i].propertyFlags & propertyFlags) == propertyFlags) 
                    {
                        return i;
                    }
                }

                throw std::runtime_error("failed to find suitable memory type!");
            }
        }
    }
}