#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include <string>
#include "Layers.hpp"
#include "ApplicationFactory.hpp"
#include "InstanceFactory.hpp"
#include "PhysicalDeviceFactory.hpp"
#include "PhysicalDeviceQueueFactory.hpp"
#include "DeviceFactory.hpp"
#include "Window.hpp"
#include "SwapchainFactory.hpp"
#include "ShaderLoader.hpp"
#include "ViewportFactory.hpp"
#include "AttachmentFactory.hpp"
#include "Renderpass.hpp"
#include "Subpass.hpp"
#include "PipelineFactory.hpp"
#include "FramebufferFactory.hpp"
#include "SemaphoreFactory.hpp"
#include "CommandBufferFactory.hpp"
#include "CommandBufferRecorder.hpp"
#include "VertexBufferFactory.hpp"
#include "TexturedImageFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            class VulkanWrapper final
            {
                private:
                    //TODO: REMOVE and load from actual vertex data
                    const std::vector<Geometry::Vertex2D> VERTICES;
                    const std::vector<uint16_t> INDICES;
                    //TODO: Load from folder
                    const std::vector<std::string> VERTEX_SHADER_PATHS;
                    const std::vector<std::string> FRAGMENT_SHADER_PATHS;
                public: 
                    VulkanWrapper();
                    ~VulkanWrapper() = default;

                    //Read-only "getter fields"
                    const std::unique_ptr<const Layers> LAYERS;
                    const std::unique_ptr<const ApplicationFactory> APPLICATION_FACTORY;
                    const std::unique_ptr<const InstanceFactory> INSTANCE_FACTORY;
                    const std::unique_ptr<const PhysicalDeviceFactory> PHYSICAL_DEVICE_FACTORY;
                    const std::unique_ptr<const PhysicalDeviceQueueFactory> PHYSICAL_DEVICE_QUEUE_FACTORY;
                    const std::unique_ptr<const DeviceFactory> DEVICE_FACTORY;
                    const std::unique_ptr<const Window> WINDOW;
                    const std::unique_ptr<const SwapchainFactory> SWAPCHAIN_FACTORY;
                    const std::unique_ptr<const ShaderLoader> SHADER_LOADER;
                    const std::unique_ptr<const ViewportFactory> VIEWPORT_FACTORY;
                    const std::unique_ptr<const AttachmentFactory> ATTACHMENT_FACTORY;
                    const std::unique_ptr<const Subpass> SUBPASS;
                    const std::unique_ptr<const Renderpass> RENDERPASS;
                    const std::unique_ptr<const PipelineFactory> PIPELINE_FACTORY;
                    const std::unique_ptr<const FramebufferFactory> FRAMEBUFFER_FACTORY;
                    const std::unique_ptr<const SemaphoreFactory> SEMAPHORE_FACTORY;
                    const std::unique_ptr<const CommandBufferFactory> COMMAND_BUFFER_FACTORY;
                    const std::unique_ptr<const TexturedImageFactory> TEXTURED_IMAGE_FACTORY;

                    //TODO: Consider using custom allocater with offset instead of initializing all buffers by hand
                    //Is not const because it will be deleted after the staging is moved to gpu
                    /*std::unique_ptr<const VertexBufferFactory> VERTEX_BUFFER_FACTORY_FOR_CPU_STAGING;
                    const std::unique_ptr<const VertexBufferFactory> VERTEX_BUFFER_FACTORY_FOR_GPU;
                    //Is not const because it will be deleted after the staging is moved to gpu
                    std::unique_ptr<const VertexBufferFactory> INDEX_BUFFER_FACTORY_FOR_CPU_STAGING;
                    const std::unique_ptr<const VertexBufferFactory> INDEX_BUFFER_FACTORY_FOR_GPU;*/
                    std::unique_ptr<const VertexBufferFactory> TEXEL_BUFFER_FACTORY_FOR_CPU_STAGING;
                    const std::unique_ptr<const VertexBufferFactory> TEXEL_BUFFER_FACTORY_FOR_GPU;
            };  
        }
    }
}
