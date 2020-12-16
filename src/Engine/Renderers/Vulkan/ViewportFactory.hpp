#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            class ViewportFactory final
            {
                public:
                    ViewportFactory(const uint32_t& windowWidth, const uint32_t& windowHeight);
                    ~ViewportFactory() = default;

                    //Read-only "getter fields"
                    const std::unique_ptr<const VkViewport> VIEWPORT;
                    const std::unique_ptr<const VkRect2D> SCISSOR;
            };
        }
    }
}