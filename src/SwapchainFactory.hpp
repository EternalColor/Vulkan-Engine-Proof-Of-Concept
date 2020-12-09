#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <stdexcept>

class SwapchainFactory final
{
    private:
        uint32_t amountOfImagesInSwapchain;

        //Read only, no smart pointer required
        const VkDevice* CACHED_DEVICE;

        std::unique_ptr<const VkSwapchainKHR> createSwapchain(const VkDevice* device, const VkSwapchainCreateInfoKHR* swapchainCreateInfo) const;
        std::unique_ptr<const VkImage[]> getImagesInSwapchain(const VkDevice* device, const VkSwapchainKHR* swapchain, uint32_t* amountOfImagesInSwapchain) const;
        std::unique_ptr<const VkImageView[]> createImageViews(const VkDevice* device, const VkImage swapchainImages[], const uint32_t& amountOfImagesInSwapchain) const;
    public:
        SwapchainFactory(const VkDevice* device, const VkSurfaceKHR* surface, const uint32_t& windowWidth, const uint32_t& windowHeight);
        ~SwapchainFactory();

        //Read-only "getter fields"
        const std::unique_ptr<const VkSwapchainCreateInfoKHR> SWAPCHAIN_CREATE_INFO;
        const std::unique_ptr<const VkSwapchainKHR> SWAPCHAIN;
        const std::unique_ptr<const VkImage[]> SWAPCHAIN_IMAGES;
        const std::unique_ptr<const VkImageView[]> SWAPCHAIN_IMAGE_VIEWS;
};