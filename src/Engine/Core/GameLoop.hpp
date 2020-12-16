#pragma once

#include <vulkan/vulkan.h>
#include <chrono>
//TODO: Remove iostream here its only for debugging
#include <iostream>
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

                void Render() const;
                void Tick(const float& deltaTime) const;
            public:
                GameLoop();
                ~GameLoop() = default;
                
                void Run() const;
        };
    }
}