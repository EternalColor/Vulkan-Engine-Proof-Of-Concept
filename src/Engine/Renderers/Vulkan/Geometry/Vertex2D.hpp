#pragma once

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <array>

namespace SnowfallEngine
{   
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            namespace Geometry
            {
                class Vertex2D final
                {
                    public:
                        glm::vec2 Position;
                        glm::vec3 Color;

                        //TODO: place somewhere else
                        static VkVertexInputBindingDescription GetBindingDescription()
                        {
                            VkVertexInputBindingDescription bindingDescription{};
                            bindingDescription.binding = 0;
                            bindingDescription.stride = sizeof(Geometry::Vertex2D);
                            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

                            return bindingDescription;
                        }

                        //TODO: place somewhere else
                        static const std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions(const VkFormat* format)
                        {            
                            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
                            attributeDescriptions[0].binding = 0;
                            attributeDescriptions[0].location = 0;
                            attributeDescriptions[0].format = *format;
                            attributeDescriptions[0].offset = offsetof(Vertex2D, Position);

                            attributeDescriptions[1].binding = 0;
                            attributeDescriptions[1].location = 1;
                            attributeDescriptions[1].format = *format;
                            attributeDescriptions[1].offset = offsetof(Vertex2D, Color);

                            return attributeDescriptions;
                        }
                };
            }
        }
    }
}