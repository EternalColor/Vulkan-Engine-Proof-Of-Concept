#include "TexturedImageFactory.hpp"

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
                //Cast constness away, otherwise it wont be accepted by stbi_image_free
                stbi_image_free(const_cast<stbi_uc*>(this->TEXEL.get()));
            }

            std::unique_ptr<const stbi_uc> TexturedImageFactory::createTexturedImage(int* textureWidth, int* textureHeight, VkDeviceSize* deviceSize) const
            {
                int texChannels = 0;
                stbi_uc* pixels = stbi_load("../textures/texture.jpg", textureWidth, textureHeight, &texChannels, STBI_rgb_alpha);
                VkDeviceSize imageSize = *textureWidth * *textureHeight * 4;

                if (!pixels) 
                {
                    throw std::runtime_error("failed to load texture image!");
                }

                return std::make_unique<stbi_uc>(pixels);
            }

            std::unique_ptr<const VkImage> TexturedImageFactory::createImage(const VkDevice* device, const int& textureWidth, const int& textureHeight) const
            {
                const VkImageCreateInfo imageInfo
                {
                    .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
                    .imageType = VK_IMAGE_TYPE_2D,
                    .extent
                    {
                        .width = static_cast<uint32_t>(textureWidth),
                        .height = static_cast<uint32_t>(textureHeight),
                        .depth = 1
                    },
                    .mipLevels = 1,
                    .arrayLayers = 1,
                    .format = VK_FORMAT_R8G8B8A8_SRGB, //TODO: Check if format is valid
                    .tiling = VK_IMAGE_TILING_OPTIMAL,
                    .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                    .usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                    .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
                    .samples = VK_SAMPLE_COUNT_1_BIT,
                    .flags = 0 // Optional
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
        }
    }
}