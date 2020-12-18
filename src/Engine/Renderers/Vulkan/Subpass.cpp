#include "Subpass.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            Subpass::Subpass(const VkAttachmentReference* attachmentReferences)
                :   //INITIALIZATION ORDER MATTERS
                    DESCRIPTION
                    {
                        new VkSubpassDescription
                        {
                            .flags = 0,                                  
                            .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,    
                            .inputAttachmentCount = 0,                               
                            .pInputAttachments = nullptr,                            
                            .colorAttachmentCount = 1,                               
                            .pColorAttachments = attachmentReferences,               
                            .pResolveAttachments = nullptr,                          
                            .pDepthStencilAttachment = nullptr,                      
                            .preserveAttachmentCount = 0,                            
                            .pPreserveAttachments = nullptr                          
                        }
                    },
                    DEPENDENCY
                    {
                        new VkSubpassDependency
                        {
                            .srcSubpass = VK_SUBPASS_EXTERNAL,                                                        
                            .dstSubpass = 0,                                                                          
                            .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,                            
                            .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,                            
                            .srcAccessMask = 0,                                                                       
                            .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                            .dependencyFlags = 0                                                                      
                        }
                    }
            {
            }
        }
    }
}