#pragma once

#include <memory>
#include <vulkan/vulkan.h>

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            class ApplicationFactory final
            {
                public:
                    ApplicationFactory();
                    ~ApplicationFactory() = default;

                    //Read-only "getter fields"
                    const std::unique_ptr<VkApplicationInfo> DEFAULT_APPLICATION_INFO;
            };
        }
    }
}