#include "PhysicalDeviceQueueFactory.hpp"

PhysicalDeviceQueueFactory::PhysicalDeviceQueueFactory(const VkPhysicalDevice* physicalDevices, const VkQueueFlagBits&& requiredQueueFlags)
    :   
        //INITIALIZER ORDER MATTERS!
        amountOfQueueFamilies { 0 },
        QUEUE_FAIMILY_PROPERTIES { this->createQueueFamilyProperties(physicalDevices, amountOfQueueFamilies) },
        DEVICE_QUEUE_CREATE_INFO { this->createDeviceQueueCreateInfo(physicalDevices, requiredQueueFlags, QUEUE_FAIMILY_PROPERTIES.get(), amountOfQueueFamilies) }
        
{

}

std::unique_ptr<const VkQueueFamilyProperties[]> PhysicalDeviceQueueFactory::createQueueFamilyProperties(const VkPhysicalDevice* physicalDevices, uint32_t& amountOfQueueFamilies) const
{
    //Assume only 1 physical device
    vkGetPhysicalDeviceQueueFamilyProperties(*physicalDevices, &amountOfQueueFamilies, nullptr);

    //Can not use <const VkQueueFamilyProperties[]> here because vulkan method requires non-const familyProperties parameter
    std::unique_ptr<VkQueueFamilyProperties[]> familyProperties = std::make_unique<VkQueueFamilyProperties[]>(amountOfQueueFamilies); 
    vkGetPhysicalDeviceQueueFamilyProperties(*physicalDevices, &amountOfQueueFamilies, familyProperties.get());

    return familyProperties;
}

std::unique_ptr<const VkDeviceQueueCreateInfo> PhysicalDeviceQueueFactory::createDeviceQueueCreateInfo(const VkPhysicalDevice* physicalDevices, const VkQueueFlagBits& requiredQueueFlags, const VkQueueFamilyProperties queueFamilyProperties[], const uint32_t& amountOfQueueFamilies) const
{
    //Find out which queue family fits the best
    for(uint32_t i = 0; i < amountOfQueueFamilies; ++i)
    {
        if(queueFamilyProperties[i].queueFlags & requiredQueueFlags)
        {
            return std::unique_ptr<const VkDeviceQueueCreateInfo>
            {
                new VkDeviceQueueCreateInfo
                {
                    VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, //sType
                    nullptr, //pNext
                    0, //flags
                    i, //queueFamilyIndex
                    queueFamilyProperties[i].queueCount, //queueCount
                    PhysicalDeviceQueueFactory::QUEUE_PRIORITIES //pQueuePriorities
                }
            };
        }
    }

    //Not found an appropiate queue family
    throw std::runtime_error("No appropiate device queue was found");
}