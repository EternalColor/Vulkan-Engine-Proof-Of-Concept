#include "SemaphoreFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            SemaphoreFactory::SemaphoreFactory(const VkDevice* device)
                :   //INITIALIZER ORDER MATTERS!
                    CACHED_DEVICE { device },
                    IMAGE_AVAILABLE { this->createSemaphore(this->CACHED_DEVICE) },
                    RENDERING_DONE { this->createSemaphore(this->CACHED_DEVICE) }
            {

            }

            SemaphoreFactory::~SemaphoreFactory()
            {
                vkDestroySemaphore(*this->CACHED_DEVICE, *this->RENDERING_DONE, nullptr);
                vkDestroySemaphore(*this->CACHED_DEVICE, *this->IMAGE_AVAILABLE, nullptr);
            }

            std::unique_ptr<const VkSemaphore> SemaphoreFactory::createSemaphore(const VkDevice* device) const
            {
                VkSemaphoreCreateInfo semaphoreCreateInfo = 
                {
                    .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0
                };

                //Can not use <const VkSemaphore> here because vulkan method requires non-const VkSemaphore parameter
                std::unique_ptr<VkSemaphore> semaphore = std::make_unique<VkSemaphore>();
                vkCreateSemaphore(*device, &semaphoreCreateInfo, nullptr, semaphore.get());

                return semaphore;
            }
        }
    }
}