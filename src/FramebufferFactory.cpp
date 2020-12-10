#include "FramebufferFactory.hpp"

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
    //Can not use <const VkFramebuffer[]> here because vulkan method requires non-const physicalDevices parameter
    std::unique_ptr<VkFramebuffer[]> framebuffers = std::make_unique<VkFramebuffer[]>(amountOfImagesInSwapchain);

    for(uint32_t i = 0; i < amountOfImagesInSwapchain; ++i)
    {
        VkFramebufferCreateInfo framebufferCreateInfo = {};
        framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferCreateInfo.pNext = nullptr;
        framebufferCreateInfo.flags = 0;
        framebufferCreateInfo.renderPass = *renderPass;
        framebufferCreateInfo.attachmentCount = 1;
        framebufferCreateInfo.pAttachments = &imageViews[i];
        framebufferCreateInfo.width = windowWidth;
        framebufferCreateInfo.height = windowHeight;
        framebufferCreateInfo.layers = 1;

        vkCreateFramebuffer(*device, &framebufferCreateInfo, nullptr, &framebuffers[i]);
    }

    return framebuffers;
}    