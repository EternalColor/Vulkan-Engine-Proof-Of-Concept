#include "PhysicalDeviceFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            PhysicalDeviceFactory::PhysicalDeviceFactory(const VkInstance* instance) 
                :   //INITIALIZATION ORDER MATTERS
                    PHYSICAL_DEVICES { this->getVkPhysicalDevices(instance) },
                    PHYSICAL_DEVICE_FEATURES { this->getVkPhysicalDeviceFeatures(this->PHYSICAL_DEVICES.get()) }
            {

            }

            std::unique_ptr<const VkPhysicalDevice[]> PhysicalDeviceFactory::getVkPhysicalDevices(const VkInstance* instance) const
            {
                //Get Physical Devices
                uint32_t physicalDeviceCount = 0;
                vkEnumeratePhysicalDevices(*instance, &physicalDeviceCount, nullptr);

                //Can not use <const VkPhysicalDevice[]> here because vulkan method requires non-const physicalDevices parameter
                std::unique_ptr<VkPhysicalDevice[]> physicalDevices = std::make_unique<VkPhysicalDevice[]>(physicalDeviceCount);
                vkEnumeratePhysicalDevices(*instance, &physicalDeviceCount, physicalDevices.get());

                return physicalDevices;
            }

            std::unique_ptr<const VkPhysicalDeviceFeatures> PhysicalDeviceFactory::getVkPhysicalDeviceFeatures(const VkPhysicalDevice* physicalDevice) const
            {
                //TODO: Make it so we can use multiple physicalDevices
                //Can not use <const VkPhysicalDeviceFeatures> here because vulkan method requires non-const VkPhysicalDeviceFeatures parameter
                std::unique_ptr<VkPhysicalDeviceFeatures> deviceFeatures = std::make_unique<VkPhysicalDeviceFeatures>();
                vkGetPhysicalDeviceFeatures(*physicalDevice, deviceFeatures.get());

                return deviceFeatures;
            }
        }
    }
}