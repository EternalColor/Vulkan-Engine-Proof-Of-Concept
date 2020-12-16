#pragma once

#include <memory>
#include <stdexcept>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include "Layers.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            class InstanceFactory final
            {
                private:
                    uint32_t extensionCount;
                    const char* const* INSTANCE_EXTENSIONS;
                    std::unique_ptr<const VkInstance> createVkInstance(const VkApplicationInfo* applicationInfo, const Layers* layers, const uint32_t& extensionCount, const char* const* extensions) const;
                public:
                    InstanceFactory(const VkApplicationInfo* applicationInfo, const Layers* layers);
                    ~InstanceFactory();

                    //Read-only "getter fields"
                    const std::unique_ptr<const VkInstance> INSTANCE;
            };
        }
    }
}