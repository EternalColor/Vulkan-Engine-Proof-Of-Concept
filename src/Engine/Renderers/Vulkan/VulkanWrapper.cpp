#include "VulkanWrapper.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            VulkanWrapper::VulkanWrapper() 
                :   //INITIALIZATION ORDER MATTERS
                    VERTEX_SHADER_PATHS 
                    { 
                        "/home/sascha/Games/VulkanTest2/build/vert.spv" 
                    },
                    FRAGMENT_SHADER_PATHS 
                    { 
                        "/home/sascha/Games/VulkanTest2/build/frag.spv" 
                    },
                    LAYERS 
                    { 
                        std::make_unique<Layers>() 
                    }, 
                    APPLICATION_FACTORY 
                    { 
                        std::make_unique<const ApplicationFactory>() 
                    },
                    INSTANCE_FACTORY 
                    { 
                        std::make_unique<const InstanceFactory>
                        (
                            this->APPLICATION_FACTORY->APPLICATION_INFO.get(), 
                            this->LAYERS.get()
                        ) 
                    },
                    PHYSICAL_DEVICE_FACTORY 
                    { 
                        std::make_unique<const PhysicalDeviceFactory>
                        (
                            this->INSTANCE_FACTORY->INSTANCE.get()
                        ) 
                    },
                    PHYSICAL_DEVICE_QUEUE_FACTORY 
                    { 
                        std::make_unique<const PhysicalDeviceQueueFactory>
                        (
                            this->PHYSICAL_DEVICE_FACTORY->BEST_PHYSICAL_DEVICE.get(), 
                            VK_QUEUE_GRAPHICS_BIT
                        ) 
                    },
                    DEVICE_FACTORY 
                    { 
                        std::make_unique<const DeviceFactory>
                        (
                            this->INSTANCE_FACTORY->INSTANCE.get(), 
                            this->PHYSICAL_DEVICE_FACTORY->BEST_PHYSICAL_DEVICE.get(), 
                            this->PHYSICAL_DEVICE_QUEUE_FACTORY->CREATE_INFO.get(), 
                            this->LAYERS.get(), 
                            this->PHYSICAL_DEVICE_FACTORY->BEST_PHYSICAL_DEVICE_FEATURES.get(), 
                            this->PHYSICAL_DEVICE_QUEUE_FACTORY->CREATE_INFO->queueFamilyIndex
                        ) 
                    }, 
                    WINDOW 
                    { 
                        std::make_unique<const Window>
                        (
                            800, 
                            600, 
                            this->APPLICATION_FACTORY->APPLICATION_INFO->pApplicationName, 
                            this->INSTANCE_FACTORY->INSTANCE.get(), 
                            this->PHYSICAL_DEVICE_FACTORY->BEST_PHYSICAL_DEVICE.get(), 
                            this->PHYSICAL_DEVICE_QUEUE_FACTORY->CREATE_INFO->queueFamilyIndex
                        ) 
                    },
                    SWAPCHAIN_FACTORY 
                    { 
                        std::make_unique<const SwapchainFactory>
                        (
                            this->DEVICE_FACTORY->DEVICE.get(),
                            &this->WINDOW->SURFACE_FORMATS[0], 
                            this->WINDOW->SURFACE.get(), 
                            this->WINDOW->GetWidth(), 
                            this->WINDOW->GetHeight()
                        ) 
                    },
                    SHADER_LOADER 
                    { 
                        std::make_unique<const ShaderLoader>
                        (
                            this->DEVICE_FACTORY->DEVICE.get(), 
                            this->VERTEX_SHADER_PATHS, 
                            this->FRAGMENT_SHADER_PATHS
                        ) 
                    },
                    VIEWPORT_FACTORY 
                    { 
                        std::make_unique<const ViewportFactory>
                        (
                            this->WINDOW->GetWidth(), 
                            this->WINDOW->GetHeight()
                        ) 
                    },
                    ATTACHMENT_FACTORY 
                    { 
                        std::make_unique<const AttachmentFactory>
                        ( 
                            &this->WINDOW->SURFACE_FORMATS[0].format 
                        ) 
                    },
                    SUBPASS 
                    { 
                        std::make_unique<const Subpass>
                        (
                            this->ATTACHMENT_FACTORY->REFERENCE.get()
                        ) 
                    },
                    RENDERPASS 
                    { 
                        std::make_unique<const Renderpass>
                        (
                            this->DEVICE_FACTORY->DEVICE.get(), 
                            this->ATTACHMENT_FACTORY->DESCRIPTION.get(), 
                            this->SUBPASS->DESCRIPTION.get(), 
                            this->SUBPASS->DEPENDENCY.get()
                        ) 
                    },
                    PIPELINE_FACTORY 
                    { 
                        std::make_unique<const PipelineFactory>
                        (
                            this->DEVICE_FACTORY->DEVICE.get(), 
                            this->SHADER_LOADER->VERTEX_SHADER_COUNT, 
                            this->SHADER_LOADER->FRAGMENT_SHADER_COUNT, 
                            this->SHADER_LOADER->VERTEX_SHADERS.get(), 
                            this->SHADER_LOADER->FRAGMENT_SHADERS.get(), 
                            this->RENDERPASS->RENDER_PASS.get(), 
                            this->VIEWPORT_FACTORY->VIEWPORT.get(), 
                            this->VIEWPORT_FACTORY->SCISSOR.get(),
                            &this->WINDOW->SURFACE_FORMATS[0].format
                        )
                    },
                    FRAMEBUFFER_FACTORY 
                    { 
                        std::make_unique<const FramebufferFactory>
                        (
                            this->DEVICE_FACTORY->DEVICE.get(), 
                            this->SWAPCHAIN_FACTORY->GetAmountOfImagesInSwapchain(), 
                            this->RENDERPASS->RENDER_PASS.get(), 
                            this->SWAPCHAIN_FACTORY->IMAGE_VIEWS.get(), 
                            this->WINDOW->GetWidth(), 
                            this->WINDOW->GetHeight()
                        ) 
                    },
                    SEMAPHORE_FACTORY 
                    {
                        std::make_unique<const SemaphoreFactory>
                        (
                            this->DEVICE_FACTORY->DEVICE.get()
                        ) 
                    },
                    COMMAND_BUFFER_FACTORY 
                    { 
                        std::make_unique<const CommandBufferFactory>
                        (
                            this->DEVICE_FACTORY->DEVICE.get(), 
                            this->PHYSICAL_DEVICE_QUEUE_FACTORY->CREATE_INFO->queueFamilyIndex, 
                            this->SWAPCHAIN_FACTORY->GetAmountOfImagesInSwapchain()
                        ) 
                    },
                    VERTEX_BUFFER_FACTORY
                    {
                       /* std::make_unique<const VertexBufferFactory>
                        (
                            this->DEVICE_FACTORY->DEVICE.get(),
                            0,
                            this->PHYSICAL_DEVICE_FACTORY->BEST_PHYSICAL_DEVICE_MEMORY_PROPERTIES.get(),
                            this->PHYSICAL_DEVICE_QUEUE_FACTORY->CREATE_INFO->queueFamilyIndex,

                        )*/
                    }
            {
                CommandBufferRecorder::RecordCommandBuffers(this->COMMAND_BUFFER_FACTORY->BUFFERS.get(), this->SWAPCHAIN_FACTORY->GetAmountOfImagesInSwapchain(), this->RENDERPASS->RENDER_PASS.get(), this->FRAMEBUFFER_FACTORY->FRAMEBUFFERS.get(), this->WINDOW->GetWidth(), this->WINDOW->GetHeight(), this->PIPELINE_FACTORY->PIPELINE.get(), this->VIEWPORT_FACTORY->VIEWPORT.get(), this->VIEWPORT_FACTORY->SCISSOR.get());
            }
        }
    }
}