#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            class SemaphoreFactory final
            {
                private:
                    //Read only, no smart pointer required
                    const VkDevice* CACHED_DEVICE;

                    std::unique_ptr<const VkSemaphore> createSemaphore(const VkDevice* device) const;
                public:
                    SemaphoreFactory(const VkDevice* device);
                    ~SemaphoreFactory();

                    //Read-only "getter fields"
                    const std::unique_ptr<const VkSemaphore> SEMAPHORE_IMAGE_AVAILABLE;
                    const std::unique_ptr<const VkSemaphore> SEMAPHORE_RENDERING_DONE;
            };
        }
    }
}