#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <stdexcept>

class FramebufferFactory final
{
    private: 
        //Read only, no smart pointer required
        const VkDevice* CACHED_DEVICE;
        const uint32_t& CACHED_AMOUNT_OF_IMAGES_IN_SWAPCHAIN;

        std::unique_ptr<const VkFramebuffer[]> createFramebuffers(const VkDevice* device, const uint32_t& amountOfImagesInSwapchain, const VkRenderPass* renderPass, const VkImageView imageViews[], const uint32_t& windowWidth, const uint32_t& windowHeight) const;
    public:
        FramebufferFactory(const VkDevice* device, const uint32_t& amountOfImagesInSwapchain, const VkRenderPass* renderPass, const VkImageView imageViews[], const uint32_t& windowWidth, const uint32_t& windowHeight);
        ~FramebufferFactory();

        //Read-only "getter fields"
        const std::unique_ptr<const VkFramebuffer[]> FRAMEBUFFERS;
};