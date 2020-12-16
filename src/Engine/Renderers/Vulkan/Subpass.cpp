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
                            0,                                  //flags
                            VK_PIPELINE_BIND_POINT_GRAPHICS,    //pipelineBindPoint
                            0,                                  //inputAttachmentCount
                            nullptr,                            //pInputAttachments
                            1,                                  //colorAttachmentCount
                            attachmentReferences,               //pColorAttachments
                            nullptr,                            //pResolveAttachments
                            nullptr,                            //pDepthStencilAttachment
                            0,                                  //preserveAttachmentCount
                            nullptr                             //pPreserveAttachments
                        }
                    },
                    DEPENDENCY
                    {
                        new VkSubpassDependency
                        {
                            VK_SUBPASS_EXTERNAL,                                                        //srcSubpass
                            0,                                                                          //dstSubpass
                            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,                              //srcStageMask
                            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,                              //dstStageMask
                            0,                                                                          //srcAccessMask
                            VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT, //dstAccessMask
                            0                                                                           //dependencyFlags
                        }
                    }
            {
            }
        }
    }
}