#include "ApplicationFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            ApplicationFactory::ApplicationFactory() 
                :   //INITIALIZATION ORDER MATTERS
                    DEFAULT_APPLICATION_INFO 
                    { 
                        new VkApplicationInfo
                        {
                            VK_STRUCTURE_TYPE_APPLICATION_INFO, //sType
                            nullptr,                            //pNext
                            "Vulkan Test",                      //pApplicationName
                            VK_MAKE_VERSION(0, 0, 0),           //applicationVersion
                            "Snowfall Engine",                  //pEngineName
                            VK_MAKE_VERSION(1, 0, 0),           //engineVersion
                            VK_API_VERSION_1_2                  //apiVersion
                        }
                    }
            {

            }
        }
    }
}
