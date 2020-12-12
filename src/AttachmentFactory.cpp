#include "AttachmentFactory.hpp"

uint32_t AttachmentFactory::attachmentCount = 0;

AttachmentFactory::AttachmentFactory(const VkFormat* format)
    :   //INITIALIZATION ORDER MATTERS
        DESCRIPTION 
        {
            new VkAttachmentDescription
            {
                0,                                  //flags
                *format,                            //format
                VK_SAMPLE_COUNT_1_BIT,              //samples
                VK_ATTACHMENT_LOAD_OP_CLEAR,        //loadOp       
                VK_ATTACHMENT_STORE_OP_STORE,       //storeOp
                VK_ATTACHMENT_LOAD_OP_DONT_CARE,    //stencilLoadOp     
                VK_ATTACHMENT_STORE_OP_DONT_CARE,   //stencilStoreOp    
                VK_IMAGE_LAYOUT_UNDEFINED,          //initialLayout     
                VK_IMAGE_LAYOUT_PRESENT_SRC_KHR     //finalLayout
            }
        },
        REFERENCE
        {
            new VkAttachmentReference
            {
                AttachmentFactory::attachmentCount,         //attachment
                VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL    //layout
            }
        }
{
    ++AttachmentFactory::attachmentCount;
}
