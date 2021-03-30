#include "BufferMemoryFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            //Constructor that is only used internally for buffers of type VkBuffer by overload "chaining"
            BufferMemoryFactory::BufferMemoryFactory(const VkDevice* device, const VkPhysicalDeviceMemoryProperties* properties, const VkBuffer* buffer, const VkMemoryPropertyFlags& propertyFlags)
                :   //INITIALIZATION ORDER MATTERS
                    CACHED_DEVICE { device },
                    MEMORY_REQUIREMENTS { this->createMemoryRequirementsForBuffer(this->CACHED_DEVICE, buffer) },
                    MEMORY { this->allocateMemory(this->CACHED_DEVICE, properties, this->MEMORY_REQUIREMENTS.get(), propertyFlags) }
            {

            }
            
            //Constructor that is only used internally for buffers of type VkImage by overload "chaining"
            BufferMemoryFactory::BufferMemoryFactory(const VkDevice* device, const VkPhysicalDeviceMemoryProperties* properties, const VkImage* image, const VkMemoryPropertyFlags& propertyFlags)
                :   //INITIALIZATION ORDER MATTERS
                    CACHED_DEVICE { device },
                    MEMORY_REQUIREMENTS { this->createMemoryRequirementsForBuffer(this->CACHED_DEVICE, image) },
                    MEMORY { this->allocateMemory(this->CACHED_DEVICE, properties, this->MEMORY_REQUIREMENTS.get(), propertyFlags) }
            {

            }

            //Constructor for vertex data
            BufferMemoryFactory::BufferMemoryFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryPropertyFlags& propertyFlags, const VkBuffer* buffer, const std::vector<Geometry::Vertex2D>* vertices, const bool&& isStagingBuffer)
            {
                if(isStagingBuffer)
                {
                    this->mapMemory(this->CACHED_DEVICE, this->MEMORY.get(), deviceSize, vertices);
                }

                this->bindMemory(this->CACHED_DEVICE, buffer, this->MEMORY.get());
            }
            
            //Constructor for indices data
            BufferMemoryFactory::BufferMemoryFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryPropertyFlags& propertyFlags, const VkBuffer* buffer, const std::vector<uint16_t>* indices, const bool&& isStagingBuffer)
            {
                if(isStagingBuffer)
                {
                    this->mapMemory(this->CACHED_DEVICE, this->MEMORY.get(), deviceSize, indices);
                }

                this->bindMemory(this->CACHED_DEVICE, buffer, this->MEMORY.get());
            }
            
            //Constructor for texel (image pixel) data
            BufferMemoryFactory::BufferMemoryFactory(const VkDevice* device, const VkDeviceSize& deviceSize, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryPropertyFlags& propertyFlags, stbi_uc* texel, const VkImage* image, const bool&& isStagingBuffer)
            {
                if(isStagingBuffer)
                {
                    this->mapMemory(this->CACHED_DEVICE, this->MEMORY.get(), deviceSize, texel);
                }

                this->bindMemory(this->CACHED_DEVICE, image, this->MEMORY.get());
            }

            BufferMemoryFactory::~BufferMemoryFactory()
            {
                vkFreeMemory(*this->CACHED_DEVICE, *this->MEMORY, nullptr);
            }
            
            std::unique_ptr<const VkMemoryRequirements> BufferMemoryFactory::createMemoryRequirementsForBuffer(const VkDevice* device, const VkBuffer* buffer) const
            {
                //Can not use <const VkMemoryRequirements> here because vulkan method requires non-const VkMemoryRequirements parameter
                std::unique_ptr<VkMemoryRequirements> memoryRequirements = std::make_unique<VkMemoryRequirements>();

                vkGetBufferMemoryRequirements(*device, *buffer, memoryRequirements.get());

                return memoryRequirements;
            }

            std::unique_ptr<const VkMemoryRequirements> BufferMemoryFactory::createMemoryRequirementsForBuffer(const VkDevice* device, const VkImage* buffer) const
            {
                //Can not use <const VkMemoryRequirements> here because vulkan method requires non-const VkMemoryRequirements parameter
                std::unique_ptr<VkMemoryRequirements> memoryRequirements = std::make_unique<VkMemoryRequirements>();

                vkGetImageMemoryRequirements(*device, *buffer, memoryRequirements.get());

                return memoryRequirements;
            }

            std::unique_ptr<const VkDeviceMemory> BufferMemoryFactory::allocateMemory(const VkDevice* device, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryRequirements* memoryRequirements, const VkMemoryPropertyFlags& propertyFlags) const
            {
                const VkMemoryAllocateInfo memoryAllocationInfo = 
                {
                    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                    .allocationSize = memoryRequirements->size,
                    .memoryTypeIndex = findMemoryType(memoryRequirements->memoryTypeBits, properties, propertyFlags) 
                };

                //Can not use <const VkDeviceMemory> here because vulkan method requires non-const VkDeviceMemory parameter
                std::unique_ptr<VkDeviceMemory> deviceMemory = std::make_unique<VkDeviceMemory>();

                if (vkAllocateMemory(*device, &memoryAllocationInfo, nullptr, deviceMemory.get()) != VK_SUCCESS)
                {
                    throw std::runtime_error("failed to allocate vertex buffer memory!");
                }      

                return deviceMemory;
            }

            void BufferMemoryFactory::bindMemory(const VkDevice* device, const VkBuffer* buffer, const VkDeviceMemory* deviceMemory) const
            {
                vkBindBufferMemory(*device, *buffer, *deviceMemory, 0);
            }

            void BufferMemoryFactory::bindMemory(const VkDevice* device, const VkImage* image, const VkDeviceMemory* deviceMemory) const
            {
                vkBindImageMemory(*device, *image, *deviceMemory, 0);
            }

            void BufferMemoryFactory::mapMemory(const VkDevice* device, const VkDeviceMemory* deviceMemory, const VkDeviceSize& deviceSize, const std::vector<Geometry::Vertex2D>* vertices) const
            {
                void* data;
                vkMapMemory(*device, *deviceMemory, 0, deviceSize, 0, &data);
                
                //Copy vertices into data
                std::memcpy(data, vertices->data(), static_cast<size_t>(deviceSize));

                vkUnmapMemory(*device, *deviceMemory);
            }

            void BufferMemoryFactory::mapMemory(const VkDevice* device, const VkDeviceMemory* deviceMemory, const VkDeviceSize& deviceSize, const std::vector<uint16_t>* indices) const
            {
                void* data;
                vkMapMemory(*device, *deviceMemory, 0, deviceSize, 0, &data);
                
                //Copy vertices into data
                std::memcpy(data, indices->data(), static_cast<size_t>(deviceSize));

                vkUnmapMemory(*device, *deviceMemory);
            }

            void BufferMemoryFactory::mapMemory(const VkDevice* device, const VkDeviceMemory* deviceMemory, const VkDeviceSize& deviceSize, stbi_uc* texel) const
            {
                void* data;
                vkMapMemory(*device, *deviceMemory, 0, deviceSize, 0, &data);
                
                //Copy vertices into data
                std::memcpy(data, texel, static_cast<size_t>(deviceSize));

                vkUnmapMemory(*device, *deviceMemory);
            }

            const uint32_t BufferMemoryFactory::findMemoryType(const uint32_t& typeFilter, const VkPhysicalDeviceMemoryProperties* properties, const VkMemoryPropertyFlags& propertyFlags) const
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
