#pragma once

#include <vulkan/vulkan.h>
#include <memory>

class PhysicalDeviceFactory final
{
    private:
        std::unique_ptr<const VkPhysicalDevice[]> getVkPhysicalDevices(const VkInstance* instance) const;
        std::unique_ptr<const VkPhysicalDeviceFeatures> getVkPhysicalDeviceFeatures(const VkPhysicalDevice* physicalDevice) const;
    public:
        PhysicalDeviceFactory(const VkInstance* instance);
        ~PhysicalDeviceFactory() = default;

        //Read-only "getter fields"
        const std::unique_ptr<const VkPhysicalDevice[]> PHYSICAL_DEVICES;
        const std::unique_ptr<const VkPhysicalDeviceFeatures> PHYSICAL_DEVICE_FEATURES;
};