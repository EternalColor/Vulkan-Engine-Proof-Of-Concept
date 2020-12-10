#include "SemaphoreFactory.hpp"

SemaphoreFactory::SemaphoreFactory(const VkDevice* device)
    :   //INITIALIZER ORDER MATTERS!
        CACHED_DEVICE { device },
        SEMAPHORE { this->createSemaphore(this->CACHED_DEVICE) }
{

}

SemaphoreFactory::~SemaphoreFactory()
{
    vkDestroySemaphore(*this->CACHED_DEVICE, *this->SEMAPHORE, nullptr);
}

std::unique_ptr<const VkSemaphore> SemaphoreFactory::createSemaphore(const VkDevice* device) const
{
    VkSemaphoreCreateInfo semaphoreCreateInfo = {};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreCreateInfo.pNext = nullptr;
    semaphoreCreateInfo.flags = 0;

    //Can not use <const VkSemaphore> here because vulkan method requires non-const physicalDevices parameter
    std::unique_ptr<VkSemaphore> semaphore = std::make_unique<VkSemaphore>();
    vkCreateSemaphore(*device, &semaphoreCreateInfo, nullptr, semaphore.get());

    return semaphore;
}