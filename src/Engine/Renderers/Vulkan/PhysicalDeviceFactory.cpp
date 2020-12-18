#include "PhysicalDeviceFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            PhysicalDeviceFactory::PhysicalDeviceFactory(const VkInstance* instance) 
                :   //INITIALIZATION ORDER MATTERS
                    BEST_PHYSICAL_DEVICE { this->getBestPhysicalDevice(instance) },
                    BEST_PHYSICAL_DEVICE_FEATURES { this->getFeaturesOfBestPhysicalDevice(this->BEST_PHYSICAL_DEVICE.get()) },
                    BEST_PHYSICAL_DEVICE_PROPERTIES { this->getPropertiesOfBestPhysicalDevice(this->BEST_PHYSICAL_DEVICE.get()) },
                    BEST_PHYSICAL_DEVICE_MEMORY_PROPERTIES { this->getMemoryPropertiesOfBestPhysicalDevice(this->BEST_PHYSICAL_DEVICE.get()) } 
            {

            }

            std::unique_ptr<const VkPhysicalDevice> PhysicalDeviceFactory::getBestPhysicalDevice(const VkInstance* instance) const
            {
                //Get Physical Devices
                uint32_t physicalDeviceCount = 0;
                vkEnumeratePhysicalDevices(*instance, &physicalDeviceCount, nullptr);
                
                VkPhysicalDevice physicalDevices[physicalDeviceCount];
                vkEnumeratePhysicalDevices(*instance, &physicalDeviceCount, physicalDevices);

                uint32_t bestIndex = 0;
                uint32_t bestScore = 0;

                for(uint32_t i = 0; i < physicalDeviceCount; ++i)
                {
                    uint32_t score = this->rateDeviceSuitability(&physicalDevices[i]);

                    //New highscore for physicalDevice found :)
                    if(score > bestScore)
                    {
                        bestIndex = i;
                        bestScore = score;
                    }
                }
                
                return std::unique_ptr<const VkPhysicalDevice>( new VkPhysicalDevice(physicalDevices[bestIndex]) );
            }

            //Score is rated by HARDCODED VALUES
            uint32_t PhysicalDeviceFactory::rateDeviceSuitability(const VkPhysicalDevice* physicalDevice) const
            {
                VkPhysicalDeviceFeatures features {};
                vkGetPhysicalDeviceFeatures(*physicalDevice, &features);

                VkPhysicalDeviceProperties properties {};
                vkGetPhysicalDeviceProperties(*physicalDevice, &properties);

                int score = 0;

                //The best device is usualy a discrete GPU
                score += properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ? 1000 : 0;
                score += properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU ? 500 : 0;
                score += properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU ? 250 : 0;

                return score;
            }

            //Intended to be used with BEST_DEVICE
            std::unique_ptr<const VkPhysicalDeviceFeatures> PhysicalDeviceFactory::getFeaturesOfBestPhysicalDevice(const VkPhysicalDevice* physicalDevice) const
            {
                //TODO: Make it so we can use multiple physicalDevices, rank them according to a performance score, then take the best device
                //Can not use <const VkPhysicalDeviceFeatures> here because vulkan method requires non-const VkPhysicalDeviceFeatures parameter
                std::unique_ptr<VkPhysicalDeviceFeatures> deviceFeatures = std::make_unique<VkPhysicalDeviceFeatures>();
                vkGetPhysicalDeviceFeatures(*physicalDevice, deviceFeatures.get());

                return deviceFeatures;
            }

            //Intended to be used with BEST_DEVICE
            std::unique_ptr<const VkPhysicalDeviceProperties> PhysicalDeviceFactory::getPropertiesOfBestPhysicalDevice(const VkPhysicalDevice* physicalDevice) const
            {
                //Can not use <const VkPhysicalDeviceProperties> here because vulkan method requires non-const VkPhysicalDeviceProperties parameter
                std::unique_ptr<VkPhysicalDeviceProperties> deviceProperties = std::make_unique<VkPhysicalDeviceProperties>();
                vkGetPhysicalDeviceProperties(*physicalDevice, deviceProperties.get());

                return deviceProperties;
            }

            std::unique_ptr<const VkPhysicalDeviceMemoryProperties> PhysicalDeviceFactory::getMemoryPropertiesOfBestPhysicalDevice(const VkPhysicalDevice* physicalDevice) const
            {
                //Can not use <const VkPhysicalDeviceMemoryProperties> here because vulkan method requires non-const VkPhysicalDeviceMemoryProperties parameter
                std::unique_ptr<VkPhysicalDeviceMemoryProperties> memoryProperties = std::make_unique<VkPhysicalDeviceMemoryProperties>();
                vkGetPhysicalDeviceMemoryProperties(*physicalDevice, memoryProperties.get());
                
                return memoryProperties;
            }
        }
    }
}