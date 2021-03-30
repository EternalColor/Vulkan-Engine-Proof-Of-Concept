#include "PipelineFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            PipelineFactory::PipelineFactory(const VkDevice* device, const size_t& vertexShaderCount, const size_t& fragmentShaderCount, const VkShaderModule vertexShaderModules[], const VkShaderModule fragmentShaderModules[], const VkRenderPass* renderPass, const VkViewport* viewport, const VkRect2D* scissor)
                :   //INITIALIZER ORDER MATTERS!
                    CACHED_DEVICE { device },
                    SHADER_STAGES { this->createShaderStages(vertexShaderCount, fragmentShaderCount, vertexShaderModules, fragmentShaderModules) },
                    PIPELINE_LAYOUT { this->createPipelineLayout(device) },
                    PIPELINE { this->createPipeline(device, vertexShaderCount + fragmentShaderCount, this->SHADER_STAGES.get(), this->PIPELINE_LAYOUT.get(), renderPass, viewport, scissor) }
            {

            }

            PipelineFactory::~PipelineFactory()
            {
                vkDestroyPipelineLayout(*this->CACHED_DEVICE, *this->PIPELINE_LAYOUT, nullptr);
                vkDestroyPipeline(*this->CACHED_DEVICE, *this->PIPELINE, nullptr);
            }

            std::unique_ptr<const VkPipelineShaderStageCreateInfo[]> PipelineFactory::createShaderStages(const size_t& vertexShaderCount, const size_t& fragmentShaderCount, const VkShaderModule vertexShaderModules[], const VkShaderModule fragmentShaderModules[]) const
            {
                //BE CAREFUL, always assign the raw pointer to the unique ptr returned by this function -> memory leak potential otherwise
                VkPipelineShaderStageCreateInfo* shaderStageCreateInfos = new VkPipelineShaderStageCreateInfo[vertexShaderCount + fragmentShaderCount];

                VkPipelineShaderStageCreateInfo vertexShaderPipelineStageCreateInfo
                {
                    .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .stage = VK_SHADER_STAGE_VERTEX_BIT,
                    .pName = "main",
                    .pSpecializationInfo = nullptr
                };

                for(size_t currentVertexShaderCount = 0; currentVertexShaderCount < vertexShaderCount; ++currentVertexShaderCount)
                {
                    vertexShaderPipelineStageCreateInfo.module = vertexShaderModules[currentVertexShaderCount]; 
                    shaderStageCreateInfos[currentVertexShaderCount] = vertexShaderPipelineStageCreateInfo;
                }

                VkPipelineShaderStageCreateInfo fragmentShaderPipelineStageCreateInfo 
                {
                    .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
                    .pName = "main",
                    .pSpecializationInfo = nullptr,
                };

                for(size_t currentFragmentShaderCount = 0; currentFragmentShaderCount < fragmentShaderCount; ++currentFragmentShaderCount)
                {
                    fragmentShaderPipelineStageCreateInfo.module = fragmentShaderModules[currentFragmentShaderCount]; 
                    shaderStageCreateInfos[vertexShaderCount + currentFragmentShaderCount] = fragmentShaderPipelineStageCreateInfo;
                }

                return std::unique_ptr<const VkPipelineShaderStageCreateInfo[]> 
                {
                    shaderStageCreateInfos
                };
            }

            std::unique_ptr<const VkPipelineLayout> PipelineFactory::createPipelineLayout(const VkDevice* device) const
            {
                const VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo
                {
                    .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .setLayoutCount = 0,
                    .pSetLayouts = nullptr,
                    .pushConstantRangeCount = 0,
                    .pPushConstantRanges = nullptr
                };

                std::unique_ptr<VkPipelineLayout> pipelineLayout { new VkPipelineLayout(VK_NULL_HANDLE) };

                vkCreatePipelineLayout(*device, &pipelineLayoutCreateInfo, nullptr, pipelineLayout.get());

                return pipelineLayout;
            }

            std::unique_ptr<const VkPipeline> PipelineFactory::createPipeline(const VkDevice* device, const uint32_t& shaderStageCount, const VkPipelineShaderStageCreateInfo shaderStageCreateInfos[], const VkPipelineLayout* layout, const VkRenderPass* renderPass, const VkViewport* viewport, const VkRect2D* scissor) const
            {
                //TODO: Place somewhere else
                VkVertexInputBindingDescription bindingDescription = Geometry::Vertex2D::GetBindingDescription();
                std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = Geometry::Vertex2D::GetAttributeDescriptions();

                const VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo 
                {
                    .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .vertexBindingDescriptionCount = 1,
                    .pVertexBindingDescriptions = &bindingDescription,
                    .vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size()),
                    .pVertexAttributeDescriptions = attributeDescriptions.data()
                };

                const VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo 
                {
                    .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
                    .primitiveRestartEnable = VK_FALSE
                };

                const VkPipelineViewportStateCreateInfo pipelineViewportStateCreateInfo
                {
                    .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .viewportCount = 1,
                    .pViewports = viewport,
                    .scissorCount = 1,
                    .pScissors = scissor
                };

                const VkPipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo
                {
                    .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .depthClampEnable = VK_FALSE,
                    .rasterizerDiscardEnable = VK_FALSE,
                    .polygonMode = VK_POLYGON_MODE_FILL,
                    .cullMode = VK_CULL_MODE_BACK_BIT,
                    .frontFace = VK_FRONT_FACE_CLOCKWISE,
                    .depthBiasEnable = VK_FALSE,
                    .depthBiasConstantFactor = 0.0f,
                    .depthBiasClamp = 0.0f,
                    .depthBiasSlopeFactor = 0.0f,
                    .lineWidth = 1.0f
                };

                //Anti Aliasing
                const VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo
                {
                    .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT, //TODO: make configurable 
                    .sampleShadingEnable = VK_FALSE,
                    .minSampleShading = 1.0f,
                    .pSampleMask = nullptr,
                    .alphaToCoverageEnable = VK_FALSE,
                    .alphaToOneEnable = VK_FALSE
                };

                const VkPipelineColorBlendAttachmentState pipelineColorBlendAttachmentState 
                {
                    .blendEnable = VK_TRUE,
                    .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
                    .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
                    .colorBlendOp = VK_BLEND_OP_ADD,
                    .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
                    .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
                    .alphaBlendOp = VK_BLEND_OP_ADD,
                    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
                };

                const VkPipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo
                {
                    .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .logicOpEnable = VK_FALSE,
                    .logicOp = VK_LOGIC_OP_NO_OP,
                    .attachmentCount = 1,
                    .pAttachments = &pipelineColorBlendAttachmentState,
                    .blendConstants =
                    {
                        0.0f,
                        0.0f,
                        0.0f,
                        1.0f
                    } 
                };
            
                const VkDynamicState dynamicStates[]
                {
                    VK_DYNAMIC_STATE_VIEWPORT,
                    VK_DYNAMIC_STATE_SCISSOR
                };

                const VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo 
                {
                    .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .dynamicStateCount = 2,
                    .pDynamicStates = dynamicStates
                };

                const VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo
                {
                    .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .stageCount = shaderStageCount,
                    .pStages = shaderStageCreateInfos,
                    .pVertexInputState = &pipelineVertexInputStateCreateInfo,
                    .pInputAssemblyState = &pipelineInputAssemblyStateCreateInfo,
                    .pTessellationState = nullptr,
                    .pViewportState = &pipelineViewportStateCreateInfo,
                    .pRasterizationState = &pipelineRasterizationStateCreateInfo,
                    .pMultisampleState = &pipelineMultisampleStateCreateInfo,
                    .pDepthStencilState = nullptr,
                    .pColorBlendState = &pipelineColorBlendStateCreateInfo,
                    .pDynamicState = &dynamicStateCreateInfo,
                    .layout = *layout,
                    .renderPass = *renderPass,
                    .subpass = 0,
                    .basePipelineHandle = VK_NULL_HANDLE,
                    .basePipelineIndex = -1
                };

                std::unique_ptr<VkPipeline> pipeline { new VkPipeline(VK_NULL_HANDLE) };
                vkCreateGraphicsPipelines(*device, VK_NULL_HANDLE, 1, &graphicsPipelineCreateInfo, nullptr, pipeline.get());

                return pipeline;
            }

        }
    }
}