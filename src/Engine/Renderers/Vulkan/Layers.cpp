#include "Layers.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            Layers::Layers() 
                :   //INITIALIZATION ORDER MATTERS
                    REQUIRED_LAYERS { "VK_LAYER_KHRONOS_validation" } 
            {

            }
        }
    }
}