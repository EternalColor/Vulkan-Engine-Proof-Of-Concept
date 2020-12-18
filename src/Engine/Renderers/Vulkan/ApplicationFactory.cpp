#include "ApplicationFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            ApplicationFactory::ApplicationFactory() 
                :   //INITIALIZATION ORDER MATTERS
                    APPLICATION_INFO 
                    { 
                        new VkApplicationInfo
                        {
                            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO, 
                            .pNext = nullptr,                            
                            .pApplicationName = "Vulkan Test",           
                            .applicationVersion = VK_MAKE_VERSION(0, 0, 0),
                            .pEngineName = "Snowfall Engine",            
                            .engineVersion = VK_MAKE_VERSION(1, 0, 0),           
                            .apiVersion = VK_API_VERSION_1_2                  
                        }
                    }
            {

            }
        }
    }
}
