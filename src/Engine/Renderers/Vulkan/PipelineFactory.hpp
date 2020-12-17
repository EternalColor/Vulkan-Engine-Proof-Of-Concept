#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include "Geometry/Vertex2D.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            class PipelineFactory final
            {
                private:
                    //Read only, no smart pointer required
                    const VkDevice* CACHED_DEVICE;

                    std::unique_ptr<const VkPipelineShaderStageCreateInfo[]> createShaderStages(const size_t& vertexShaderCount, const size_t& fragmentShaderCount, const VkShaderModule vertexShaderModules[], const VkShaderModule fragmentShaderModules[]) const;
                    std::unique_ptr<const VkPipelineLayout> createPipelineLayout(const VkDevice* device) const;
                    std::unique_ptr<const VkPipeline> createPipeline(const VkDevice* device, const uint32_t& shaderStageCount, const VkPipelineShaderStageCreateInfo shaderStageCreateInfos[], const VkPipelineLayout* layout, const VkRenderPass* renderPass, const VkViewport* viewport, const VkRect2D* scissor, const VkFormat* format) const;
                public:
                    PipelineFactory(const VkDevice* device, const size_t& vertexShaderCount, const size_t& fragmentShaderCount, const VkShaderModule vertexShaderModules[], const VkShaderModule fragmentShaderModules[], const VkRenderPass* renderPass, const VkViewport* viewport, const VkRect2D* scissor, const VkFormat* format);
                    ~PipelineFactory();

                    //Read-only "getter fields"
                    const std::unique_ptr<const VkPipelineShaderStageCreateInfo[]> SHADER_STAGES;
                    const std::unique_ptr<const VkPipelineLayout> PIPELINE_LAYOUT;
                    const std::unique_ptr<const VkPipeline> PIPELINE;
            };
        }
    }
}