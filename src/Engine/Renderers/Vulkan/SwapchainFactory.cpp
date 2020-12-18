#include "SwapchainFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            SwapchainFactory::SwapchainFactory(const VkDevice* device, const VkSurfaceFormatKHR* format, const VkSurfaceKHR* surface, const uint32_t& windowWidth, const uint32_t& windowHeight)
                :   //INITIALIZATION ORDER MATTERS
                    amountOfImagesInSwapchain { 0 },
                    CACHED_DEVICE { device },
                    CREATE_INFO 
                    {
                        new VkSwapchainCreateInfoKHR
                        {
                            .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR, 
                            .pNext = nullptr,                                     
                            .flags = 0,                                           
                            .surface = *surface,                                  
                            .minImageCount = 3,                                   
                            .imageFormat = format->format,                        
                            .imageColorSpace = format->colorSpace,                
                            .imageExtent = VkExtent2D { windowWidth, windowHeight},
                            .imageArrayLayers = 1,                                
                            .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,    
                            .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,        
                            .queueFamilyIndexCount = 0,                           
                            .pQueueFamilyIndices = nullptr,                       
                            .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
                            .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,  
                            .presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR,         
                            .clipped = VK_TRUE,                                   
                            .oldSwapchain = VK_NULL_HANDLE,                       
                        }
                    },
                    SWAPCHAIN { this->createSwapchain(device, this->CREATE_INFO.get()) },
                    IMAGES { this->getImagesInSwapchain(device, this->SWAPCHAIN.get(), &this->amountOfImagesInSwapchain) },
                    IMAGE_VIEWS { this->createImageViews(device, format, this->IMAGES.get(), this->amountOfImagesInSwapchain)}
            {

            }

            SwapchainFactory::~SwapchainFactory()
            {
                for(uint32_t i = 0; i < this->amountOfImagesInSwapchain; ++i)
                {
                    vkDestroyImageView(*this->CACHED_DEVICE, this->IMAGE_VIEWS[i], nullptr);
                    //TODO: Check why not delete
                    //vkDestroyImage(*this->CACHED_DEVICE, this->SWAPCHAIN_IMAGES[i], nullptr);
                }
                
                vkDestroySwapchainKHR(*this->CACHED_DEVICE, *this->SWAPCHAIN, nullptr);
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

            std::unique_ptr<const VkImageView[]> SwapchainFactory::createImageViews(const VkDevice* device, const VkSurfaceFormatKHR* format, const VkImage swapchainImages[], const uint32_t& amountOfImagesInSwapchain) const
            {
                std::unique_ptr<VkImageView[]> imageViews = std::make_unique<VkImageView[]>(amountOfImagesInSwapchain);

                VkImageViewCreateInfo imageViewCreateInfo 
                {
                    .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .viewType = VK_IMAGE_VIEW_TYPE_2D, //TODO: Check if 2D is appropiate view type
                    .format = format->format,
                    .components
                    {
                        .r = VK_COMPONENT_SWIZZLE_IDENTITY,
                        .g = VK_COMPONENT_SWIZZLE_IDENTITY, 
                        .b = VK_COMPONENT_SWIZZLE_IDENTITY, 
                        .a = VK_COMPONENT_SWIZZLE_IDENTITY,
                    },
                    .subresourceRange 
                    { 
                        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                        .baseMipLevel = 0,
                        .levelCount = 1, //We only have 1 mip level
                        .baseArrayLayer = 0,
                        .layerCount = 1,
                    }
                };

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

            const uint32_t& SwapchainFactory::GetAmountOfImagesInSwapchain() const
            {
                return this->amountOfImagesInSwapchain;
            }
        }
    }
}