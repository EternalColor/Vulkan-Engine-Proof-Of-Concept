#pragma once

#include <memory>
#include <vector>
#include <stdexcept>
#include <vulkan/vulkan.h>
#include "Layers.hpp"

class DeviceFactory
{
    private:
        const std::vector<const char*> DEVICE_EXTENSIONS;
        std::unique_ptr<const VkDevice> createVkDevice(const VkInstance* vkInstance, const VkPhysicalDevice physicalDevices[], const VkDeviceQueueCreateInfo* physicalDeviceQueue, const Layers* layers, const std::vector<const char*>& extensions, const VkPhysicalDeviceFeatures* physicalDeviceFeatures) const;
        std::unique_ptr<const VkQueue> createVkQueue(const VkDevice* device, const uint32_t& queueFamilyIndex) const;
    public:
        DeviceFactory(const VkInstance* vkInstance, const VkPhysicalDevice physicalDevices[], const VkDeviceQueueCreateInfo* physicalDeviceQueue, const Layers* layers, const VkPhysicalDeviceFeatures* physicalDeviceFeatures, const uint32_t& queueFamilyIndex);
        ~DeviceFactory();

        //Read-only "getter fields"
        const std::unique_ptr<const VkDevice> DEVICE;
        const std::unique_ptr<const VkQueue> DEVICE_QUEUE;  
};