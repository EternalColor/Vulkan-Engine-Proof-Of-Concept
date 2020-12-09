#pragma once

#include <vulkan/vulkan.h>
#include <memory>

class ViewportFactory
{
    private: 
        std::unique_ptr<const VkViewport> createViewport(const uint32_t& windowWidth, const uint32_t& windowHeight) const;
        std::unique_ptr<const VkRect2D> createScissor(const uint32_t& windowWidth, const uint32_t& windowHeight) const;
    public:
        ViewportFactory(const uint32_t& windowWidth, const uint32_t& windowHeight);
        ~ViewportFactory() = default;

        //Read-only "getter fields"
        const std::unique_ptr<const VkViewport> VIEWPORT;
        const std::unique_ptr<const VkRect2D> SCISSOR;
};