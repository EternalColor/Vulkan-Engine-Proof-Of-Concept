#include "Renderpass.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            Renderpass::Renderpass(const VkDevice* device, const VkAttachmentDescription attachmentDescriptions[], const VkSubpassDescription subpassDescriptions[], const VkSubpassDependency subpassDependencies[])
                :   //INITIALIZATION ORDER MATTERS
                    CACHED_DEVICE { device },
                    RENDER_PASS { this->createRenderpass(device, attachmentDescriptions, subpassDescriptions, subpassDependencies) }
            {

            }

            Renderpass::~Renderpass()
            {
                vkDestroyRenderPass(*this->CACHED_DEVICE, *this->RENDER_PASS, nullptr);
            }

            std::unique_ptr<const VkRenderPass> Renderpass::createRenderpass(const VkDevice* device, const VkAttachmentDescription attachmentDescriptions[], const VkSubpassDescription subpassDescriptions[], const VkSubpassDependency subpassDependencies[]) const
            {
                const VkRenderPassCreateInfo renderPassCreateInfo 
                {
                    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .attachmentCount = 1,
                    .pAttachments = attachmentDescriptions,
                    .subpassCount = 1,
                    .pSubpasses = subpassDescriptions,
                    .dependencyCount = 1,
                    .pDependencies = subpassDependencies
                };
                
                //Can not use <const VkRenderPass> here because vulkan method requires non-const device parameter
                std::unique_ptr<VkRenderPass> renderPass { new VkRenderPass(VK_NULL_HANDLE) };

                vkCreateRenderPass(*device, &renderPassCreateInfo, nullptr, renderPass.get());

                return renderPass;
            }
        }
    }
}