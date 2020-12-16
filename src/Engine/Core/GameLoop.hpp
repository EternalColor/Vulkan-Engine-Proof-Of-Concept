#pragma once

#include <vulkan/vulkan.h>
//TODO: Make it work with generic window and not just vulkan
#include "../Renderers/Vulkan/VulkanWrapper.hpp"

namespace SnowfallEngine
{
    namespace Core
    {
        class GameLoop final
        {
            private:
                //Read-only "getter fields"
                const std::unique_ptr<const Renderers::VulkanRenderer::VulkanWrapper> renderWrapper;

            public:
                GameLoop();
                ~GameLoop() = default;
                
                void Run() const;
        };
    }
}