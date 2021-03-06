#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <memory>
#include "../../libraries/stb/stb_image.h"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            //Class to load image data into a texture via stb_image.h library
            class TexturedImageFactory
            {
                private:
                    int textureWidth;
                    int textureHeight;
                    VkDeviceSize size;

                    //this method also initializes textureWidth, textureHeight and deviceSize (the public const members of this factory) by passing them as pointers
                    std::unique_ptr<stbi_uc[]> createTexturedImage(int* textureWidth, int* textureHeight, VkDeviceSize* deviceSize) const;
                    std::unique_ptr<const VkImage> createImage(const VkDevice* device, const int& textureWidth, const int& textureHeight) const;
                    std::unique_ptr<const VkMemoryRequirements> getMemoryRequirements(const VkDevice* device, const VkImage* image) const;
                public:
                    TexturedImageFactory(const VkDevice* device);
                    ~TexturedImageFactory();

                    //Read-only "getter fields"
                    //Array of texture pixels
                    const std::unique_ptr<stbi_uc[]> TEXEL;
                    //Image treated later on as a buffer to send to GPU
                    const std::unique_ptr<const VkImage> IMAGE;
                    const std::unique_ptr<const VkMemoryRequirements> MEMORY_REQUIREMENT;

                    const int& GetTextureWidth() const;
                    const int& GetTextureHeight() const;
                    const VkDeviceSize& GetDeviceSize() const;
            };
        }
    }
}