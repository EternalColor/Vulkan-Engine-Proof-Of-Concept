#include "ViewportFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            ViewportFactory::ViewportFactory(const uint32_t& windowWidth, const uint32_t& windowHeight)
                :   //INITIALIZATION ORDER MATTERS
                    VIEWPORT 
                    { 
                        new VkViewport
                        {
                            .x = 0.0f,         
                            .y = 0.0f,        
                            .width = windowWidth,  
                            .height = windowHeight,
                            .minDepth = 0.0f,      
                            .maxDepth = 1.0f       
                        }
                    },
                    SCISSOR 
                    { 
                        new VkRect2D
                        {
                            VkOffset2D{ 0, 0 },                     //offset
                            VkExtent2D{ windowWidth, windowHeight } //extend
                        } 
                    }
            {

            }
        }
    }
}