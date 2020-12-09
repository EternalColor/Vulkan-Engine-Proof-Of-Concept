#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <stdexcept>

class PhysicalDeviceQueueFactory final
{
    private:
        static constexpr inline float QUEUE_PRIORITIES[] = { 1.0f };
        uint32_t amountOfQueueFamilies;

        std::unique_ptr<const VkQueueFamilyProperties[]> createQueueFamilyProperties(const VkPhysicalDevice* physicalDevices, uint32_t& amountOfQueueFamilies) const;
        std::unique_ptr<const VkDeviceQueueCreateInfo> createDeviceQueueCreateInfo(const VkPhysicalDevice* physicalDevices, const VkQueueFlagBits& requiredQueueFlags, const VkQueueFamilyProperties queueFamilyProperties[], const uint32_t& amountOfQueueFamilies) const;
    public:
        PhysicalDeviceQueueFactory(const VkPhysicalDevice* physicalDevices, const VkQueueFlagBits&& requiredQueueFlags);
        ~PhysicalDeviceQueueFactory() = default;

        //Read-only "getter fields"
        const std::unique_ptr<const VkQueueFamilyProperties[]> QUEUE_FAIMILY_PROPERTIES;
        const std::unique_ptr<const VkDeviceQueueCreateInfo> DEVICE_QUEUE_CREATE_INFO;  
};