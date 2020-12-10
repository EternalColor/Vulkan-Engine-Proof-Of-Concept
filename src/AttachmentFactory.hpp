#pragma once

#include <vulkan/vulkan.h>
#include <memory>

class AttachmentFactory final
{
    private:
        static uint32_t attachmentCount;
    public:
        AttachmentFactory(const VkFormat* format);
        ~AttachmentFactory() = default;

        //Read-only "getter fields"
        const std::unique_ptr<const VkAttachmentDescription> DESCRIPTION;
        const std::unique_ptr<const VkAttachmentReference> REFERENCE;
};