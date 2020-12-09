#pragma once

#include <vulkan/vulkan.h>
#include <memory>

class Attachment
{
    public:
        Attachment();
        ~Attachment();

        const std::unique_ptr<VkAttachmentDescription> DESCRIPTION;
        const std::unique_ptr<VkAttachmentReference> REFERENCE;
};