#include "Runtime.hpp"

Runtime::Runtime() 
    :   //INITIALIZATION ORDER MATTERS
        VERTEX_SHADER_PATHS { },
        FRAGMENT_SHADER_PATHS {  },
        LAYERS { std::make_unique<Layers>() }, 
        APPLICATION_FACTORY { std::make_unique<ApplicationFactory>() },
        INSTANCE_FACTORY { std::make_unique<InstanceFactory>(this->APPLICATION_FACTORY->DEFAULT_APPLICATION_INFO.get(), this->LAYERS.get()) },
        PHYSICAL_DEVICE_FACTORY { std::make_unique<PhysicalDeviceFactory>(this->INSTANCE_FACTORY->INSTANCE.get()) },
        PHYSICAL_DEVICE_QUEUE_FACTORY { std::make_unique<PhysicalDeviceQueueFactory>(this->PHYSICAL_DEVICE_FACTORY->PHYSICAL_DEVICES.get(), VK_QUEUE_GRAPHICS_BIT) },
        DEVICE_FACTORY { std::make_unique<DeviceFactory>(this->INSTANCE_FACTORY->INSTANCE.get(), this->PHYSICAL_DEVICE_FACTORY->PHYSICAL_DEVICES.get(), this->PHYSICAL_DEVICE_QUEUE_FACTORY->DEVICE_QUEUE_CREATE_INFO.get(), this->LAYERS.get(), this->PHYSICAL_DEVICE_FACTORY->PHYSICAL_DEVICE_FEATURES.get(), this->PHYSICAL_DEVICE_QUEUE_FACTORY->DEVICE_QUEUE_CREATE_INFO->queueFamilyIndex) }, 
        WINDOW { std::make_unique<const Window>(800, 600, this->APPLICATION_FACTORY->DEFAULT_APPLICATION_INFO->pApplicationName, this->INSTANCE_FACTORY->INSTANCE.get(), &this->PHYSICAL_DEVICE_FACTORY->PHYSICAL_DEVICES[0], this->PHYSICAL_DEVICE_QUEUE_FACTORY->DEVICE_QUEUE_CREATE_INFO->queueFamilyIndex) },
        SWAPCHAIN_FACTORY { std::make_unique<const SwapchainFactory>(this->DEVICE_FACTORY->DEVICE.get(), this->WINDOW->SURFACE.get(), this->WINDOW->GetWidth(), this->WINDOW->GetHeight()) },
        SHADER_LOADER { std::make_unique<const ShaderLoader>(this->DEVICE_FACTORY->DEVICE.get(), this->VERTEX_SHADER_PATHS, this->FRAGMENT_SHADER_PATHS) },
        VIEWPORT_FACTORY { std::make_unique<const ViewportFactory>(this->WINDOW->GetWidth(), this->WINDOW->GetHeight()) },
        GAME_LOOP { std::make_unique<const GameLoop>(this->WINDOW.get()) }
{
}