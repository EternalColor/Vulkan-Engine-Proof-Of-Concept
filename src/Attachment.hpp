#pragma once

#include <vulkan/vulkan.h>
#include <memory>

class Attachment final
{
    private:
        static uint32_t attachmentCount;
    public:
        Attachment(const VkFormat* format);
        ~Attachment() = default;

        //Read-only "getter fields"
        const std::unique_ptr<const VkAttachmentDescription> DESCRIPTION;
        const std::unique_ptr<const VkAttachmentReference> REFERENCE;
};