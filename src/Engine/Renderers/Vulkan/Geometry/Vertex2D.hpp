#pragma once

#include <vulkan/vulkan.h>
#include "../../libraries/glm/glm/glm.hpp"
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
                        Vertex2D(glm::vec2 position, glm::vec3 color) : Position { position }, Color { color }{};
                        Vertex2D() = default;

                        glm::vec2 Position;
                        glm::vec3 Color;

                        //TODO: place somewhere else
                        static const VkVertexInputBindingDescription GetBindingDescription()
                        {
                            VkVertexInputBindingDescription bindingDescription{};
                            bindingDescription.binding = 0;
                            bindingDescription.stride = sizeof(Vertex2D);
                            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

                            return bindingDescription;
                        }

                        //TODO: place somewhere else
                        static const std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions()
                        {            
                            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
                            attributeDescriptions[0].binding = 0;
                            attributeDescriptions[0].location = 0;
                            attributeDescriptions[0].format = VK_FORMAT_R32G32B32A32_SFLOAT; //TODO find format
                            attributeDescriptions[0].offset = offsetof(Vertex2D, Position);

                            attributeDescriptions[1].binding = 0;
                            attributeDescriptions[1].location = 1;
                            attributeDescriptions[1].format = VK_FORMAT_R32G32B32A32_SFLOAT; //TODO find format
                            attributeDescriptions[1].offset = offsetof(Vertex2D, Color);

                            return attributeDescriptions;
                        }
                };
            }
        }
    }
}