#include "VulkanWrapper.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            VulkanWrapper::VulkanWrapper() 
                :   //INITIALIZATION ORDER MATTERS
                   /* VERTICES
                    {
                        //POSITION        COLOR
                        {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                        {{0.5f, -0.5f},  {0.0f, 1.0f, 0.0f}},
                        {{0.5f, 0.5f},   {0.0f, 0.0f, 1.0f}},
                        {{-0.5f, 0.5f},  {1.0f, 1.0f, 1.0f}}
                    },
                    INDICES
                    {
                        0, 1, 2, 2, 3, 0
                    },*/
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
                            this->VIEWPORT_FACTORY->SCISSOR.get()
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
                    /*VERTEX_BUFFER_FACTORY_FOR_CPU_STAGING
                    {
                        std::make_unique<const VertexBufferFactory>
                        (
                            this->DEVICE_FACTORY->DEVICE.get(),
                            sizeof(this->VERTICES[0]) * this->VERTICES.size(),
                            this->PHYSICAL_DEVICE_FACTORY->BEST_PHYSICAL_DEVICE_MEMORY_PROPERTIES.get(),
                            this->PHYSICAL_DEVICE_QUEUE_FACTORY->CREATE_INFO->queueFamilyIndex,
                            nullptr,
                            static_cast<VkMemoryPropertyFlagBits>(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT),
                            static_cast<VkBufferUsageFlags>(VK_BUFFER_USAGE_TRANSFER_SRC_BIT),
                            &this->VERTICES,
                            true
                        )
                    },
                    VERTEX_BUFFER_FACTORY_FOR_GPU
                    {
                        std::make_unique<const VertexBufferFactory>
                        (
                            this->DEVICE_FACTORY->DEVICE.get(),
                            sizeof(this->VERTICES[0]) * this->VERTICES.size(),
                            this->PHYSICAL_DEVICE_FACTORY->BEST_PHYSICAL_DEVICE_MEMORY_PROPERTIES.get(),
                            this->PHYSICAL_DEVICE_QUEUE_FACTORY->CREATE_INFO->queueFamilyIndex,
                            nullptr,
                            static_cast<VkMemoryPropertyFlagBits>(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
                            static_cast<VkBufferUsageFlags>(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)
                        )
                    },
                    INDEX_BUFFER_FACTORY_FOR_CPU_STAGING
                    {
                        std::make_unique<const VertexBufferFactory>
                        (
                            this->DEVICE_FACTORY->DEVICE.get(),
                            sizeof(this->INDICES[0]) * this->INDICES.size(),
                            this->PHYSICAL_DEVICE_FACTORY->BEST_PHYSICAL_DEVICE_MEMORY_PROPERTIES.get(),
                            this->PHYSICAL_DEVICE_QUEUE_FACTORY->CREATE_INFO->queueFamilyIndex,
                            nullptr,
                            static_cast<VkMemoryPropertyFlagBits>(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT),
                            static_cast<VkBufferUsageFlags>(VK_BUFFER_USAGE_TRANSFER_SRC_BIT),
                            &this->INDICES
                        )
                    },
                    INDEX_BUFFER_FACTORY_FOR_GPU
                    {
                        std::make_unique<const VertexBufferFactory>
                        (
                            this->DEVICE_FACTORY->DEVICE.get(),
                            sizeof(this->INDICES[0]) * this->INDICES.size(),
                            this->PHYSICAL_DEVICE_FACTORY->BEST_PHYSICAL_DEVICE_MEMORY_PROPERTIES.get(),
                            this->PHYSICAL_DEVICE_QUEUE_FACTORY->CREATE_INFO->queueFamilyIndex,
                            nullptr,
                            static_cast<VkMemoryPropertyFlagBits>(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
                            static_cast<VkBufferUsageFlags>(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
                        )
                    }*/
                    TEXTURED_IMAGE_FACTORY
                    {
                        std::make_unique<const TexturedImageFactory>
                        (
                            this->DEVICE_FACTORY->DEVICE.get()
                        )
                    },
                    TEXEL_BUFFER_FACTORY_FOR_CPU_STAGING
                    {
                        std::make_unique<const VertexBufferFactory>
                        (
                            this->DEVICE_FACTORY->DEVICE.get(),
                            this->TEXTURED_IMAGE_FACTORY->GetDeviceSize(),
                            this->PHYSICAL_DEVICE_FACTORY->BEST_PHYSICAL_DEVICE_MEMORY_PROPERTIES.get(),
                            this->PHYSICAL_DEVICE_QUEUE_FACTORY->CREATE_INFO->queueFamilyIndex,
                            nullptr,
                            static_cast<VkMemoryPropertyFlagBits>(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT),
                            static_cast<VkBufferUsageFlags>(VK_BUFFER_USAGE_TRANSFER_SRC_BIT),
                            this->TEXTURED_IMAGE_FACTORY->TEXEL.get(),
                            this->TEXTURED_IMAGE_FACTORY->IMAGE.get(),
                            true
                        )
                    },
                    TEXEL_BUFFER_FACTORY_FOR_GPU
                    {
                        std::make_unique<const VertexBufferFactory>
                        (
                            this->DEVICE_FACTORY->DEVICE.get(),
                            this->TEXTURED_IMAGE_FACTORY->GetDeviceSize(),
                            this->PHYSICAL_DEVICE_FACTORY->BEST_PHYSICAL_DEVICE_MEMORY_PROPERTIES.get(),
                            this->PHYSICAL_DEVICE_QUEUE_FACTORY->CREATE_INFO->queueFamilyIndex,
                            nullptr,
                            static_cast<VkMemoryPropertyFlagBits>(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT),
                            static_cast<VkBufferUsageFlags>(VK_BUFFER_USAGE_TRANSFER_SRC_BIT),
                            this->TEXTURED_IMAGE_FACTORY->TEXEL.get(),
                            this->TEXTURED_IMAGE_FACTORY->IMAGE.get(),
                            false
                        )
                    }
            {
                //Copy indexs staging buffer to GPU buffer
               /* CommandBufferRecorder::CopyBuffer
                (
                    this->DEVICE_FACTORY->DEVICE.get(),
                    this->DEVICE_FACTORY->QUEUE.get(),
                    this->INDEX_BUFFER_FACTORY_FOR_CPU_STAGING->BUFFER.get(),
                    this->INDEX_BUFFER_FACTORY_FOR_GPU->BUFFER.get(),
                    sizeof(this->INDICES[0]) * this->INDICES.size(),
                    this->COMMAND_BUFFER_FACTORY->POOL.get()
                );

                //We dont need the staging buffer anymore so we can delete it
                this->INDEX_BUFFER_FACTORY_FOR_CPU_STAGING.reset();

                //Copy vertex staging buffer to GPU buffer
                CommandBufferRecorder::CopyBuffer
                (
                    this->DEVICE_FACTORY->DEVICE.get(),
                    this->DEVICE_FACTORY->QUEUE.get(),
                    this->VERTEX_BUFFER_FACTORY_FOR_CPU_STAGING->BUFFER.get(),
                    this->VERTEX_BUFFER_FACTORY_FOR_GPU->BUFFER.get(),
                    sizeof(this->VERTICES[0]) * this->VERTICES.size(),
                    this->COMMAND_BUFFER_FACTORY->POOL.get()
                );

                //We dont need the staging buffer anymore so we can delete it
                this->VERTEX_BUFFER_FACTORY_FOR_CPU_STAGING.reset();


                CommandBufferRecorder::RecordCommandBuffers
                (
                    this->COMMAND_BUFFER_FACTORY->BUFFERS.get(), 
                    this->SWAPCHAIN_FACTORY->GetAmountOfImagesInSwapchain(), 
                    this->RENDERPASS->RENDER_PASS.get(), 
                    this->FRAMEBUFFER_FACTORY->FRAMEBUFFERS.get(), 
                    this->WINDOW->GetWidth(), 
                    this->WINDOW->GetHeight(), 
                    this->PIPELINE_FACTORY->PIPELINE.get(), 
                    this->VIEWPORT_FACTORY->VIEWPORT.get(), 
                    this->VIEWPORT_FACTORY->SCISSOR.get(),  
                    this->VERTEX_BUFFER_FACTORY_FOR_GPU->BUFFER.get(),
                    static_cast<uint32_t>(this->INDICES.size()),
                    this->INDEX_BUFFER_FACTORY_FOR_GPU->BUFFER.get()
                );*/

                //Copy Texel staging buffer to GPU buffer
                CommandBufferRecorder::CopyBuffer
                (
                    this->DEVICE_FACTORY->DEVICE.get(),
                    this->DEVICE_FACTORY->QUEUE.get(),
                    this->TEXEL_BUFFER_FACTORY_FOR_CPU_STAGING->BUFFER.get(),
                    this->TEXEL_BUFFER_FACTORY_FOR_GPU->BUFFER.get(),
                    static_cast<uint32_t>(this->TEXEL_BUFFER_FACTORY_FOR_GPU->DEVICE_SIZE),
                    this->COMMAND_BUFFER_FACTORY->POOL.get()
                );

                //We dont need the staging buffer anymore so we can delete it
                this->TEXEL_BUFFER_FACTORY_FOR_CPU_STAGING.reset();

                CommandBufferRecorder::RecordCommandBuffers
                (
                    this->COMMAND_BUFFER_FACTORY->BUFFERS.get(), 
                    this->SWAPCHAIN_FACTORY->GetAmountOfImagesInSwapchain(), 
                    this->RENDERPASS->RENDER_PASS.get(), 
                    this->FRAMEBUFFER_FACTORY->FRAMEBUFFERS.get(), 
                    this->WINDOW->GetWidth(), 
                    this->WINDOW->GetHeight(), 
                    this->PIPELINE_FACTORY->PIPELINE.get(), 
                    this->VIEWPORT_FACTORY->VIEWPORT.get(), 
                    this->VIEWPORT_FACTORY->SCISSOR.get(),  
                    this->TEXEL_BUFFER_FACTORY_FOR_GPU->BUFFER.get(),
                    static_cast<uint32_t>(this->TEXEL_BUFFER_FACTORY_FOR_GPU->DEVICE_SIZE),
                    this->TEXEL_BUFFER_FACTORY_FOR_GPU->BUFFER.get()
                );
            }
        }
    }
}