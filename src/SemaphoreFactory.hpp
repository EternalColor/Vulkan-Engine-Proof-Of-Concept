#pragma once

#include <vulkan/vulkan.h>
#include <memory>

class SemaphoreFactory final
{
    private:
        //Read only, no smart pointer required
        const VkDevice* CACHED_DEVICE;

        std::unique_ptr<const VkSemaphore> createSemaphore(const VkDevice* device) const;
    public:
        SemaphoreFactory(const VkDevice* device);
        ~SemaphoreFactory();

        const std::unique_ptr<const VkSemaphore> SEMAPHORE;
};