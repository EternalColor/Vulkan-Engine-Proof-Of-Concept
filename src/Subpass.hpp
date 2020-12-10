#pragma once

#include <vulkan/vulkan.h>
#include <memory>

class Subpass final
{
    public:
        Subpass(const VkAttachmentReference* attachmentReferences);
        ~Subpass() = default;

        //Read-only "getter fields"
        const std::unique_ptr<const VkSubpassDescription> DESCRIPTION;
        const std::unique_ptr<const VkSubpassDependency> DEPENDENCY;
};