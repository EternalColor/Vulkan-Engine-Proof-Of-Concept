#include "InstanceFactory.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
            InstanceFactory::InstanceFactory(const VkApplicationInfo* applicationInfo, const Layers* layers) 
                :   //INITIALIZATION ORDER MATTERS
                    //GLFW must be initialized!
                    extensionCount { 0 },
                    INSTANCE_EXTENSIONS { glfwGetRequiredInstanceExtensions(&extensionCount) },
                    INSTANCE { this->createVkInstance(applicationInfo, layers, this->extensionCount, this->INSTANCE_EXTENSIONS) }
            {

            }

            InstanceFactory::~InstanceFactory()
            {
                vkDestroyInstance(*this->INSTANCE, nullptr);
            }

            std::unique_ptr<const VkInstance> InstanceFactory::createVkInstance(const VkApplicationInfo* applicationInfo, const Layers* layers, const uint32_t& extensionCount, const char* const* extensions) const
            {
                //Can not use <const VkInstance> here because vulkan method requires non-const instance parameter
                std::unique_ptr<VkInstance> instance { new VkInstance(VK_NULL_HANDLE) }; 

                VkInstanceCreateInfo instanceCreateInfo 
                {
                    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .pApplicationInfo = applicationInfo,
                    .enabledLayerCount = layers->REQUIRED_LAYERS.size(),
                    .ppEnabledLayerNames = layers->REQUIRED_LAYERS.data(),
                    .enabledExtensionCount = extensionCount,
                    .ppEnabledExtensionNames = extensions
                };
                
                if(vkCreateInstance(&instanceCreateInfo, nullptr, instance.get()) != VK_SUCCESS)
                {
                    throw std::runtime_error("Error creating instance");
                }

                return instance;
            }
        }
    }
}