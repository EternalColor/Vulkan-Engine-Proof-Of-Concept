#include "TexturedImageFactory.hpp"

//According to doccumentation this define needs to be here, so the whole STB_IMAGE code is only copied once into this cpp module
#define STB_IMAGE_IMPLEMENTATION
#include "../../libraries/stb/stb_image.h"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            TexturedImageFactory::TexturedImageFactory(const VkDevice* device)   
                :   //INITIALIZATION ORDER MATTERS
                    textureWidth { 0 },
                    textureHeight { 0 },
                    size { 0 },
                    TEXEL { this->createTexturedImage(&this->textureWidth, &this->textureHeight, &this->size) },
                    IMAGE { this->createImage(device, this->textureWidth, this->textureHeight) },
                    MEMORY_REQUIREMENT { this->getMemoryRequirements(device, this->IMAGE.get()) }
            {

            }

            TexturedImageFactory::~TexturedImageFactory()
            {
                stbi_image_free(this->TEXEL.get());
            }

            std::unique_ptr<stbi_uc> TexturedImageFactory::createTexturedImage(int* textureWidth, int* textureHeight, VkDeviceSize* deviceSize) const
            {
                int texChannels = 0;

                //textureWidth, textureHeight and deviceSize will be returned by pointer
                std::unique_ptr<stbi_uc> pixels { stbi_load("/home/sascha/Games/VulkanTest2/textures/texture.jpg", textureWidth, textureHeight, &texChannels, STBI_rgb_alpha) };
                *deviceSize = *textureWidth * *textureHeight * 4;

                if (!pixels) 
                {
                    throw std::runtime_error("failed to load texture image!");
                }

                return pixels;
            }

            std::unique_ptr<const VkImage> TexturedImageFactory::createImage(const VkDevice* device, const int& textureWidth, const int& textureHeight) const
            {
                const VkImageCreateInfo imageInfo
                {
                    .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0, // Optional
                    .imageType = VK_IMAGE_TYPE_2D,
                    .format = VK_FORMAT_R8G8B8A8_SRGB, //TODO: Check if format is valid
                    .extent
                    {
                        .width = static_cast<uint32_t>(textureWidth),
                        .height = static_cast<uint32_t>(textureHeight),
                        .depth = 1
                    },
                    .mipLevels = 1,
                    .arrayLayers = 1,
                    .samples = VK_SAMPLE_COUNT_1_BIT,
                    .tiling = VK_IMAGE_TILING_OPTIMAL,
                    .usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                    .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
                    .queueFamilyIndexCount = 0,
                    .pQueueFamilyIndices = nullptr,
                    .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
                };

                //Can not use <const VkImage> here because vulkan method requires non-const VkImage parameter
                std::unique_ptr<VkImage> textureImage { new VkImage(VK_NULL_HANDLE) };

                if (vkCreateImage(*device, &imageInfo, nullptr, textureImage.get()) != VK_SUCCESS) 
                {
                    throw std::runtime_error("failed to create image!");
                }

                return textureImage;
            }

            std::unique_ptr<const VkMemoryRequirements> TexturedImageFactory::getMemoryRequirements(const VkDevice* device, const VkImage* image) const
            {
                //Can not use <const VkMemoryRequirements> here because vulkan method requires non-const VkMemoryRequirements parameter
                std::unique_ptr<VkMemoryRequirements> memoryRequirements = std::make_unique<VkMemoryRequirements>();
                vkGetImageMemoryRequirements(*device, *image, memoryRequirements.get());

                return memoryRequirements;
            }

            const int& TexturedImageFactory::GetTextureWidth() const
            {
                return this->textureWidth;
            }

            const int& TexturedImageFactory::GetTextureHeight() const
            {
                return this->textureHeight;
            }

            const VkDeviceSize& TexturedImageFactory::GetDeviceSize() const
            {
                return this->size;
            }
        }
    }
}