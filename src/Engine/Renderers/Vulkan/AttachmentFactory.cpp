#include "AttachmentFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            uint32_t AttachmentFactory::attachmentCount = 0;

            AttachmentFactory::AttachmentFactory(const VkFormat* format)
                :   //INITIALIZATION ORDER MATTERS
                    DESCRIPTION 
                    {
                        new VkAttachmentDescription
                        {
                            .flags = 0,                                 
                            .format = *format,                          
                            .samples = VK_SAMPLE_COUNT_1_BIT,           
                            .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,      
                            .storeOp = VK_ATTACHMENT_STORE_OP_STORE,    
                            .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,  
                            .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,        
                            .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR     
                        }
                    },
                    REFERENCE
                    {
                        new VkAttachmentReference
                        {
                            .attachment = AttachmentFactory::attachmentCount,
                            .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
                        }
                    }
            {
                ++AttachmentFactory::attachmentCount;
            }
        }
    }
}
