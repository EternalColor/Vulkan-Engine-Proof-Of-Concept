#include <vulkan/vulkan.h>
#include <stdexcept>
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            class TexturedImageFactory
            {
                private:
                    int textureWidth;
                    int textureHeight;
                    VkDeviceSize size;

                    //this method also initializes textureWidth, textureHeight and deviceSize (the public const members of this factory)
                    std::unique_ptr<const stbi_uc> createTexturedImage(int* textureWidth, int* textureHeight, VkDeviceSize* deviceSize) const;
                    std::unique_ptr<const VkImage> createImage(const VkDevice* device, const int& textureWidth, const int& textureHeight) const;
                    std::unique_ptr<const VkMemoryRequirements> getMemoryRequirements(const VkDevice* device, const VkImage* image) const;
                public:
                    TexturedImageFactory(const VkDevice* device);
                    ~TexturedImageFactory();

                    //Read-only "getter fields"s
                    const std::unique_ptr<const stbi_uc> TEXEL;
                    const std::unique_ptr<const VkImage> IMAGE;
                    const std::unique_ptr<const VkMemoryRequirements> MEMORY_REQUIREMENT;
            };
        }
    }
}