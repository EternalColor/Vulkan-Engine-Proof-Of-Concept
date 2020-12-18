#include "FramebufferFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            FramebufferFactory::FramebufferFactory(const VkDevice* device, const uint32_t& amountOfImagesInSwapchain, const VkRenderPass* renderPass, const VkImageView imageViews[], const uint32_t& windowWidth, const uint32_t& windowHeight)
                :   //INITIALIZATION ORDER MATTERS
                    CACHED_DEVICE { device }, 
                    CACHED_AMOUNT_OF_IMAGES_IN_SWAPCHAIN { amountOfImagesInSwapchain }, 
                    FRAMEBUFFERS { this->createFramebuffers(device, this->CACHED_AMOUNT_OF_IMAGES_IN_SWAPCHAIN, renderPass, imageViews, windowWidth, windowHeight) }
            {

            }

            FramebufferFactory::~FramebufferFactory()
            {
                for(uint32_t i = 0; i < this->CACHED_AMOUNT_OF_IMAGES_IN_SWAPCHAIN; ++i)
                {
                    vkDestroyFramebuffer(*this->CACHED_DEVICE, this->FRAMEBUFFERS[i], nullptr);
                }
            }

            std::unique_ptr<const VkFramebuffer[]> FramebufferFactory::createFramebuffers(const VkDevice* device, const uint32_t& amountOfImagesInSwapchain, const VkRenderPass* renderPass, const VkImageView imageViews[], const uint32_t& windowWidth, const uint32_t& windowHeight) const
            {
                std::unique_ptr<VkFramebuffer[]> framebuffers = std::make_unique<VkFramebuffer[]>(amountOfImagesInSwapchain);

                VkFramebufferCreateInfo framebufferCreateInfo 
                {
                    .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .renderPass = *renderPass,
                    .attachmentCount = 1,
                    .width = windowWidth,
                    .height = windowHeight,
                    .layers = 1
                };

                for(uint32_t i = 0; i < amountOfImagesInSwapchain; ++i)
                {
                    framebufferCreateInfo.pAttachments = &imageViews[i];

                    if(vkCreateFramebuffer(*device, &framebufferCreateInfo, nullptr, &framebuffers[i]) != VK_SUCCESS)
                    {
                        std::runtime_error("Error creating framebuffer");
                    }
                }

                return framebuffers;
            }    
        }
    }
}