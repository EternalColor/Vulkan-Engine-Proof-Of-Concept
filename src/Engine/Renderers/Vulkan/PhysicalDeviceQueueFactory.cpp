#include "PhysicalDeviceQueueFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            PhysicalDeviceQueueFactory::PhysicalDeviceQueueFactory(const VkPhysicalDevice* physicalDevice, const VkQueueFlagBits&& requiredQueueFlags)
                :   //INITIALIZER ORDER MATTERS!
                    CREATE_INFO { this->createDeviceQueueCreateInfo(physicalDevice, requiredQueueFlags) }
                    
            {

            }

            std::unique_ptr<const VkDeviceQueueCreateInfo> PhysicalDeviceQueueFactory::createDeviceQueueCreateInfo(const VkPhysicalDevice* physicalDevice, const VkQueueFlagBits& requiredQueueFlags) const
            {
                //Assume only 1 physical device
                uint32_t amountOfQueueFamilies = 0;
                vkGetPhysicalDeviceQueueFamilyProperties(*physicalDevice, &amountOfQueueFamilies, nullptr);

                VkQueueFamilyProperties familyProperties[amountOfQueueFamilies]; 
                vkGetPhysicalDeviceQueueFamilyProperties(*physicalDevice, &amountOfQueueFamilies, familyProperties);

                //Find out which queue family fits the best
                for(uint32_t i = 0; i < amountOfQueueFamilies; ++i)
                {
                    if(familyProperties[i].queueFlags & requiredQueueFlags)
                    {
                        return std::unique_ptr<const VkDeviceQueueCreateInfo>
                        {
                            new VkDeviceQueueCreateInfo
                            {
                                VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, //sType
                                nullptr, //pNext
                                0, //flags
                                i, //queueFamilyIndex
                                familyProperties[i].queueCount, //queueCount
                                PhysicalDeviceQueueFactory::QUEUE_PRIORITIES //pQueuePriorities
                            }
                        };
                    }
                }

                //Not found an appropiate queue family
                throw std::runtime_error("No appropiate device queue was found");
            }
        }
    }
}