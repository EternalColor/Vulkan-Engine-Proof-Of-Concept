#include "PipelineFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            PipelineFactory::PipelineFactory(const VkDevice* device, const size_t& vertexShaderCount, const size_t& fragmentShaderCount, const VkShaderModule vertexShaderModules[], const VkShaderModule fragmentShaderModules[], const VkRenderPass* renderPass, const VkViewport* viewport, const VkRect2D* scissor, const VkFormat* format)
                :   //INITIALIZER ORDER MATTERS!
                    CACHED_DEVICE { device },
                    SHADER_STAGES { this->createShaderStages(vertexShaderCount, fragmentShaderCount, vertexShaderModules, fragmentShaderModules) },
                    PIPELINE_LAYOUT { this->createPipelineLayout(device) },
                    PIPELINE { this->createPipeline(device, vertexShaderCount + fragmentShaderCount, this->SHADER_STAGES.get(), this->PIPELINE_LAYOUT.get(), renderPass, viewport, scissor, format) }
            {

            }

            PipelineFactory::~PipelineFactory()
            {
                vkDestroyPipelineLayout(*this->CACHED_DEVICE, *this->PIPELINE_LAYOUT, nullptr);
                vkDestroyPipeline(*this->CACHED_DEVICE, *this->PIPELINE, nullptr);
            }

            std::unique_ptr<const VkPipelineShaderStageCreateInfo[]> PipelineFactory::createShaderStages(const size_t& vertexShaderCount, const size_t& fragmentShaderCount, const VkShaderModule vertexShaderModules[], const VkShaderModule fragmentShaderModules[]) const
            {
                VkPipelineShaderStageCreateInfo* shaderStageCreateInfos = new VkPipelineShaderStageCreateInfo[vertexShaderCount + fragmentShaderCount];

                VkPipelineShaderStageCreateInfo vertexShaderPipelineStageCreateInfo = {};
                vertexShaderPipelineStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
                vertexShaderPipelineStageCreateInfo.pNext = nullptr;
                vertexShaderPipelineStageCreateInfo.flags = 0;
                vertexShaderPipelineStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
                vertexShaderPipelineStageCreateInfo.pName = "main";
                vertexShaderPipelineStageCreateInfo.pSpecializationInfo = nullptr;
                
                for(size_t currentVertexShaderCount = 0; currentVertexShaderCount < vertexShaderCount; ++currentVertexShaderCount)
                {
                    vertexShaderPipelineStageCreateInfo.module = vertexShaderModules[currentVertexShaderCount]; 
                    shaderStageCreateInfos[currentVertexShaderCount] = vertexShaderPipelineStageCreateInfo;
                }

                VkPipelineShaderStageCreateInfo fragmentShaderPipelineStageCreateInfo = {};
                fragmentShaderPipelineStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
                fragmentShaderPipelineStageCreateInfo.pNext = nullptr;
                fragmentShaderPipelineStageCreateInfo.flags = 0;
                fragmentShaderPipelineStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT; 
                fragmentShaderPipelineStageCreateInfo.pName = "main";
                fragmentShaderPipelineStageCreateInfo.pSpecializationInfo = nullptr;

                for(size_t currentFragmentShaderCount = 0; currentFragmentShaderCount < fragmentShaderCount; ++currentFragmentShaderCount)
                {
                    fragmentShaderPipelineStageCreateInfo.module = fragmentShaderModules[currentFragmentShaderCount]; 
                    shaderStageCreateInfos[vertexShaderCount + currentFragmentShaderCount] = fragmentShaderPipelineStageCreateInfo;
                }

                return std::unique_ptr<VkPipelineShaderStageCreateInfo[]> 
                {
                    shaderStageCreateInfos
                };
            }

            std::unique_ptr<const VkPipelineLayout> PipelineFactory::createPipelineLayout(const VkDevice* device) const
            {
                VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
                pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
                pipelineLayoutCreateInfo.pNext = nullptr;
                pipelineLayoutCreateInfo.flags = 0;
                pipelineLayoutCreateInfo.setLayoutCount = 0;
                pipelineLayoutCreateInfo.pSetLayouts = nullptr;
                pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
                pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;

                std::unique_ptr<VkPipelineLayout> pipelineLayout { new VkPipelineLayout(VK_NULL_HANDLE) };

                vkCreatePipelineLayout(*device, &pipelineLayoutCreateInfo, nullptr, pipelineLayout.get());

                return pipelineLayout;
            }

            std::unique_ptr<const VkPipeline> PipelineFactory::createPipeline(const VkDevice* device, const uint32_t& shaderStageCount, const VkPipelineShaderStageCreateInfo shaderStageCreateInfos[], const VkPipelineLayout* layout, const VkRenderPass* renderPass, const VkViewport* viewport, const VkRect2D* scissor, const VkFormat* format) const
            {
                //TODO: Dont use auto
                //TODO: Place somewhere else
                auto bindingDescription = Geometry::Vertex2D::GetBindingDescription();
                auto attributeDescriptions = Geometry::Vertex2D::GetAttributeDescriptions(format);

                VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo = {};
                pipelineVertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
                pipelineVertexInputStateCreateInfo.pNext = nullptr;
                pipelineVertexInputStateCreateInfo.flags = 0;
                pipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
                pipelineVertexInputStateCreateInfo.pVertexBindingDescriptions = &bindingDescription;
                pipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
                pipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

                VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo = {};
                pipelineInputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
                pipelineInputAssemblyStateCreateInfo.pNext = nullptr;
                pipelineInputAssemblyStateCreateInfo.flags = 0;
                pipelineInputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
                pipelineInputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

                VkPipelineViewportStateCreateInfo pipelineViewportStateCreateInfo = {};
                pipelineViewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
                pipelineViewportStateCreateInfo.pNext = nullptr;
                pipelineViewportStateCreateInfo.flags = 0;
                pipelineViewportStateCreateInfo.viewportCount = 1;
                pipelineViewportStateCreateInfo.pViewports = viewport;
                pipelineViewportStateCreateInfo.scissorCount = 1 ;
                pipelineViewportStateCreateInfo.pScissors = scissor;

                VkPipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo = {};
                pipelineRasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
                pipelineRasterizationStateCreateInfo.pNext = nullptr;
                pipelineRasterizationStateCreateInfo.flags = 0;
                pipelineRasterizationStateCreateInfo.depthClampEnable = VK_FALSE; 
                pipelineRasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
                pipelineRasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
                pipelineRasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
                pipelineRasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
                pipelineRasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
                pipelineRasterizationStateCreateInfo.depthBiasConstantFactor = 0.0f;
                pipelineRasterizationStateCreateInfo.depthBiasClamp = 0.0f;
                pipelineRasterizationStateCreateInfo.depthBiasSlopeFactor = 0.0f;
                pipelineRasterizationStateCreateInfo.lineWidth = 1.0f;

                //Anti Aliasing
                VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo = {};
                pipelineMultisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
                pipelineMultisampleStateCreateInfo.pNext = nullptr;
                pipelineMultisampleStateCreateInfo.flags = 0;
                pipelineMultisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT; //TODO: make configurable 
                pipelineMultisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
                pipelineMultisampleStateCreateInfo.minSampleShading = 1.0f;
                pipelineMultisampleStateCreateInfo.pSampleMask = nullptr;
                pipelineMultisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE;
                pipelineMultisampleStateCreateInfo.alphaToOneEnable = VK_FALSE;

                VkPipelineColorBlendAttachmentState pipelineColorBlendAttachmentState = {};
                pipelineColorBlendAttachmentState.blendEnable = VK_TRUE;
                pipelineColorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA; 
                pipelineColorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
                pipelineColorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
                pipelineColorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
                pipelineColorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
                pipelineColorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;
                pipelineColorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

                VkPipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo = {};
                pipelineColorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
                pipelineColorBlendStateCreateInfo.pNext = nullptr;
                pipelineColorBlendStateCreateInfo.flags = 0;
                pipelineColorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
                pipelineColorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_NO_OP;
                pipelineColorBlendStateCreateInfo.attachmentCount = 1;
                pipelineColorBlendStateCreateInfo.pAttachments = &pipelineColorBlendAttachmentState;
                pipelineColorBlendStateCreateInfo.blendConstants[0] = 0.0f;
                pipelineColorBlendStateCreateInfo.blendConstants[1] = 0.0f;
                pipelineColorBlendStateCreateInfo.blendConstants[2] = 0.0f;
                pipelineColorBlendStateCreateInfo.blendConstants[3] = 1.0f;

                VkDynamicState dynamicStates[] = 
                {
                    VK_DYNAMIC_STATE_VIEWPORT,
                    VK_DYNAMIC_STATE_SCISSOR
                };

                VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = {};
                dynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
                dynamicStateCreateInfo.pNext = nullptr;
                dynamicStateCreateInfo.flags = 0;
                dynamicStateCreateInfo.dynamicStateCount = 2;
                dynamicStateCreateInfo.pDynamicStates = dynamicStates;

                VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo = {};
                graphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
                graphicsPipelineCreateInfo.pNext = nullptr;
                graphicsPipelineCreateInfo.flags = 0;
                graphicsPipelineCreateInfo.stageCount = shaderStageCount;
                graphicsPipelineCreateInfo.pStages = shaderStageCreateInfos;
                graphicsPipelineCreateInfo.pVertexInputState = &pipelineVertexInputStateCreateInfo;
                graphicsPipelineCreateInfo.pInputAssemblyState = &pipelineInputAssemblyStateCreateInfo;
                graphicsPipelineCreateInfo.pTessellationState = nullptr;
                graphicsPipelineCreateInfo.pViewportState = &pipelineViewportStateCreateInfo;
                graphicsPipelineCreateInfo.pRasterizationState = &pipelineRasterizationStateCreateInfo;
                graphicsPipelineCreateInfo.pMultisampleState = &pipelineMultisampleStateCreateInfo;
                graphicsPipelineCreateInfo.pDepthStencilState = nullptr;
                graphicsPipelineCreateInfo.pColorBlendState = &pipelineColorBlendStateCreateInfo;
                graphicsPipelineCreateInfo.pDynamicState = &dynamicStateCreateInfo;
                graphicsPipelineCreateInfo.layout = *layout;
                graphicsPipelineCreateInfo.renderPass = *renderPass;
                graphicsPipelineCreateInfo.subpass = 0;
                graphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
                graphicsPipelineCreateInfo.basePipelineIndex = -1;

                std::unique_ptr<VkPipeline> pipeline { new VkPipeline(VK_NULL_HANDLE) };
                vkCreateGraphicsPipelines(*device, VK_NULL_HANDLE, 1, &graphicsPipelineCreateInfo, nullptr, pipeline.get());

                return pipeline;
            }

        }
    }
}