#include "SwapchainFactory.hpp"

SwapchainFactory::SwapchainFactory(const VkSurfaceKHR* surface, const uint32_t& windowWidth, const uint32_t& windowHeight, const VkDevice* device)
    :   amountOfImagesInSwapchain { 0 },
        SWAPCHAIN_CREATE_INFO 
        {
            new VkSwapchainCreateInfoKHR
            {
                VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR, //sType
                nullptr,                                     //pNext
                0,                                           //flags
                *surface,                                    //surface
                3,                                           //minImageCount
                VK_FORMAT_B8G8R8A8_SRGB,                     //imageFormat
                VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,           //imageColorSpace
                VkExtent2D { windowWidth, windowHeight},     //imageExtent
                1,                                           //imageArrayLayers
                VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,         //imageUsage
                VK_SHARING_MODE_EXCLUSIVE,                   //imageSharingMode
                0,                                           //queueFamilyIndex
                nullptr,                                     //queueFamilyIndecies
                VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,       //preTransform
                VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,           //compositeAlpha
                VK_PRESENT_MODE_IMMEDIATE_KHR,               //presentMode
                VK_TRUE,                                     //clipped
                nullptr                                      //oldSwapchain
            }
        },
        SWAPCHAIN { this->createSwapchain(device, this->SWAPCHAIN_CREATE_INFO.get()) },
        SWAPCHAIN_IMAGES { this->getImagesInSwapchain(device, this->SWAPCHAIN.get(), &this->amountOfImagesInSwapchain) },
        SWAPCHAIN_IMAGE_VIEWS { this->createImageViews(device, this->SWAPCHAIN_IMAGES.get(), this->amountOfImagesInSwapchain)}
{

}

SwapchainFactory::~SwapchainFactory()
{
    
}

std::unique_ptr<const VkSwapchainKHR> SwapchainFactory::createSwapchain(const VkDevice* device, const VkSwapchainCreateInfoKHR* swapchainCreateInfo) const
{
    //Can not use <const VkSwapchainKHR> here because vulkan method requires non-const swapchain parameter
    std::unique_ptr<VkSwapchainKHR> swapchain { new VkSwapchainKHR(VK_NULL_HANDLE) };
    vkCreateSwapchainKHR(*device, swapchainCreateInfo, nullptr, swapchain.get());

    return swapchain;
}

std::unique_ptr<const VkImage[]> SwapchainFactory::getImagesInSwapchain(const VkDevice* device, const VkSwapchainKHR* swapchain, uint32_t* amountOfImagesInSwapchain) const
{
    vkGetSwapchainImagesKHR(*device, *swapchain, amountOfImagesInSwapchain, nullptr);

    //Can not use <const VkImage[]> here because vulkan method requires non-const swapchain parameter
    std::unique_ptr<VkImage[]> swapchainImages = std::make_unique<VkImage[]>(*amountOfImagesInSwapchain);
    vkGetSwapchainImagesKHR(*device, *swapchain, amountOfImagesInSwapchain, swapchainImages.get());

    return swapchainImages;
}

std::unique_ptr<const VkImageView[]> SwapchainFactory::createImageViews(const VkDevice* device, const VkImage swapchainImages[], const uint32_t& amountOfImagesInSwapchain) const
{
    std::unique_ptr<VkImageView[]> imageViews = std::make_unique<VkImageView[]>(amountOfImagesInSwapchain);

    VkImageViewCreateInfo imageViewCreateInfo = {};
    imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewCreateInfo.pNext = nullptr;
    imageViewCreateInfo.flags = 0;
    imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D; //TODO: Check if 2D is appropiate view type
    imageViewCreateInfo.format = VK_FORMAT_B8G8R8A8_SRGB;
    imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY; 
    imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY; 
    imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
    imageViewCreateInfo.subresourceRange.levelCount = 1; //We only have 1 mip level
    imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
    imageViewCreateInfo.subresourceRange.layerCount = 1;

    for(uint32_t i = 0; i < amountOfImagesInSwapchain; i++)
    {
        imageViewCreateInfo.image = swapchainImages[i]; 

        if(vkCreateImageView(*device, &imageViewCreateInfo, nullptr, &imageViews[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("Image View could not be created");
        }   
    }

    return imageViews;
}