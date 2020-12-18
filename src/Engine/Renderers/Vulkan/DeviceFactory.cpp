#include "DeviceFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            DeviceFactory::DeviceFactory(const VkInstance* vkInstance, const VkPhysicalDevice* physicalDevices, const VkDeviceQueueCreateInfo* deviceQueueCreateInfo, const Layers* layers, const VkPhysicalDeviceFeatures* physicalDeviceFeatures, const uint32_t& queueFamilyIndex) 
                :   //INITIALIZATION ORDER MATTERS
                    DEVICE_EXTENSIONS { VK_KHR_SWAPCHAIN_EXTENSION_NAME },
                    DEVICE { this->createVkDevice(vkInstance, physicalDevices, deviceQueueCreateInfo, layers, this->DEVICE_EXTENSIONS, physicalDeviceFeatures) },
                    QUEUE { this->createVkQueue(this->DEVICE.get(), queueFamilyIndex) }
            {
                
            }

            DeviceFactory::~DeviceFactory()
            {
                vkDestroyDevice(*this->DEVICE, nullptr);
            }

            std::unique_ptr<const VkDevice> DeviceFactory::createVkDevice(const VkInstance* vkInstance, const VkPhysicalDevice physicalDevices[], const VkDeviceQueueCreateInfo* deviceQueueCreateInfo, const Layers* layers, const std::vector<const char*>& extensions, const VkPhysicalDeviceFeatures* physicalDeviceFeatures) const
            {
                const VkDeviceCreateInfo deviceCreateInfo 
                {
                    .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .queueCreateInfoCount = 1,
                    .pQueueCreateInfos = deviceQueueCreateInfo,
                    .enabledLayerCount = static_cast<uint32_t>(layers->REQUIRED_LAYERS.size()),
                    .ppEnabledLayerNames = layers->REQUIRED_LAYERS.data(),
                    .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
                    .ppEnabledExtensionNames = extensions.data(),
                    .pEnabledFeatures = physicalDeviceFeatures
                };
                
                //Can not use <const VkDevice> here because vulkan method requires non-const device parameter
                std::unique_ptr<VkDevice> device { new VkDevice(VK_NULL_HANDLE) };

                //TODO: Choose better device than just 0
                if(vkCreateDevice(physicalDevices[0], &deviceCreateInfo, nullptr, device.get()) != VK_SUCCESS)
                {
                    throw std::runtime_error("Error creating device");
                }

                return device;
            }

            std::unique_ptr<const VkQueue> DeviceFactory::createVkQueue(const VkDevice* device, const uint32_t& queueFamilyIndex) const
            {
                //Can not use <const VkQueue> here because vulkan method requires non-const queue parameter
                std::unique_ptr<VkQueue> vkQueue { new VkQueue(VK_NULL_HANDLE) };

                //TODO: Check if 0 here is valid for queueIndex
                vkGetDeviceQueue(*device, queueFamilyIndex, 0, vkQueue.get());

                return vkQueue;
            }
        }
    }
}