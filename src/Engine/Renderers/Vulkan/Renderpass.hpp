#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            class Renderpass final
            {
                private:
                    //Read only, no smart pointer required
                    const VkDevice* CACHED_DEVICE;

                    std::unique_ptr<const VkRenderPass> createRenderpass(const VkDevice* device, const VkAttachmentDescription attachmentDescriptions[], const VkSubpassDescription subpassDescriptions[], const VkSubpassDependency subpassDependencies[]) const;
                public:
                    Renderpass(const VkDevice* device, const VkAttachmentDescription attachmentDescriptions[], const VkSubpassDescription subpassDescriptions[], const VkSubpassDependency subpassDependencies[]);
                    ~Renderpass();

                    const std::unique_ptr<const VkRenderPass> RENDER_PASS;
            };
        }
    }
}