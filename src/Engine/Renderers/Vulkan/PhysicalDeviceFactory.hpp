#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <memory>

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            class PhysicalDeviceFactory final
            {
                private:
                    std::unique_ptr<const VkPhysicalDevice> getBestPhysicalDevice(const VkInstance* instance) const;
                    uint32_t rateDeviceSuitability(const VkPhysicalDevice* physicalDevice) const;

                    std::unique_ptr<const VkPhysicalDeviceFeatures> getFeaturesOfBestPhysicalDevice(const VkPhysicalDevice* physicalDevice) const;
                    std::unique_ptr<const VkPhysicalDeviceProperties> getPropertiesOfBestPhysicalDevice(const VkPhysicalDevice* physicalDevice) const;
                    std::unique_ptr<const VkPhysicalDeviceMemoryProperties> getMemoryPropertiesOfBestPhysicalDevice(const VkPhysicalDevice* physicalDevice) const;
                public:
                    PhysicalDeviceFactory(const VkInstance* instance);
                    ~PhysicalDeviceFactory() = default;

                    //Read-only "getter fields"
                    const std::unique_ptr<const VkPhysicalDevice> BEST_PHYSICAL_DEVICE;
                    const std::unique_ptr<const VkPhysicalDeviceFeatures> BEST_PHYSICAL_DEVICE_FEATURES;
                    const std::unique_ptr<const VkPhysicalDeviceProperties> BEST_PHYSICAL_DEVICE_PROPERTIES;
                    const std::unique_ptr<const VkPhysicalDeviceMemoryProperties> BEST_PHYSICAL_DEVICE_MEMORY_PROPERTIES;
            };
        }
    }
}
