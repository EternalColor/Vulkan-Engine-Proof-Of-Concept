#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <stdexcept>

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            class PhysicalDeviceQueueFactory final
            {
                private:
                    static constexpr inline float QUEUE_PRIORITIES[] = { 1.0f };
                    
                    std::unique_ptr<const VkDeviceQueueCreateInfo> createDeviceQueueCreateInfo(const VkPhysicalDevice* physicalDevice, const VkQueueFlagBits& requiredQueueFlags) const;
                public:
                    PhysicalDeviceQueueFactory(const VkPhysicalDevice* physicalDevice, const VkQueueFlagBits&& requiredQueueFlags);
                    ~PhysicalDeviceQueueFactory() = default;

                    //Read-only "getter fields"
                    const std::unique_ptr<const VkDeviceQueueCreateInfo> DEVICE_QUEUE_CREATE_INFO;  
            };
        }
    }
}