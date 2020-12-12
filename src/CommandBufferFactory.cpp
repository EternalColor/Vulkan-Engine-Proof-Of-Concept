#include "CommandBufferFactory.hpp"

CommandBufferFactory::CommandBufferFactory(const VkDevice* device, const uint32_t& queueFamilyIndex, const uint32_t&& bufferCount)
    :   //INITIALIZATION ORDER MATTERS
        CACHED_DEVICE { device },
        BUFFER_COUNT { bufferCount },
        POOL { this->createCommandPool(device, queueFamilyIndex) },
        BUFFERS { this->createCommandBuffers(device, this->POOL.get(), this->BUFFER_COUNT) }
{
    
}

CommandBufferFactory::~CommandBufferFactory()
{
    vkFreeCommandBuffers(*this->CACHED_DEVICE, *this->POOL, this->BUFFER_COUNT, this->BUFFERS.get());
    vkDestroyCommandPool(*this->CACHED_DEVICE, *this->POOL, nullptr);
}

std::unique_ptr<const VkCommandPool> CommandBufferFactory::createCommandPool(const VkDevice* device, const uint32_t& queueFamilyIndex) const
{
    VkCommandPoolCreateInfo commandPoolCreateInfo = {};
    commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolCreateInfo.pNext = nullptr;
    commandPoolCreateInfo.flags = 0;
    commandPoolCreateInfo.queueFamilyIndex = queueFamilyIndex;

    //Can not use <const VkCommandPool> here because vulkan method requires non-const physicalDevices parameter
    std::unique_ptr<VkCommandPool> commandPool { new VkCommandPool(VK_NULL_HANDLE) };
    if(vkCreateCommandPool(*device, &commandPoolCreateInfo, nullptr, commandPool.get()) != VK_SUCCESS)
    {
        throw new std::runtime_error("Failed to create command pool.");
    }

    return commandPool;
}

std::unique_ptr<const VkCommandBuffer[]> CommandBufferFactory::createCommandBuffers(const VkDevice* device, const VkCommandPool* commandPool, const uint32_t& bufferCount) const
{
    VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
    commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocateInfo.pNext = nullptr;
    commandBufferAllocateInfo.commandPool = *commandPool;
    commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferAllocateInfo.commandBufferCount = bufferCount;

    //Can not use <const VkCommandBuffer[]> here because vulkan method requires non-const physicalDevices parameter
    std::unique_ptr<VkCommandBuffer[]> commandBuffers = std::make_unique<VkCommandBuffer[]>(bufferCount);
    
    if(vkAllocateCommandBuffers(*device, &commandBufferAllocateInfo, commandBuffers.get())!= VK_SUCCESS)
    {
        throw new std::runtime_error("Failed to allocate command buffers.");
    }

    return commandBuffers;
}