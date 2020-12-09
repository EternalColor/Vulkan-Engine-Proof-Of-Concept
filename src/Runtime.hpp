#pragma once

#include <memory>
#include "Layers.hpp"
#include "ApplicationFactory.hpp"
#include "InstanceFactory.hpp"
#include "PhysicalDeviceFactory.hpp"
#include "PhysicalDeviceQueueFactory.hpp"
#include "DeviceFactory.hpp"
#include "Window.hpp"
#include "SwapchainFactory.hpp"
#include "GameLoop.hpp"

class Runtime final
{
    private:
        //Read-only "getter fields"
        const std::unique_ptr<const Layers> LAYERS;
        const std::unique_ptr<const ApplicationFactory> APPLICATION_FACTORY;
        const std::unique_ptr<const InstanceFactory> INSTANCE_FACTORY;
        const std::unique_ptr<const PhysicalDeviceFactory> PHYSICAL_DEVICE_FACTORY;
        const std::unique_ptr<const PhysicalDeviceQueueFactory> PHYSICAL_DEVICE_QUEUE_FACTORY;
        const std::unique_ptr<const DeviceFactory> DEVICE_FACTORY;
        const std::unique_ptr<const Window> WINDOW;
        const std::unique_ptr<const SwapchainFactory> SWAPCHAIN_FACTORY;
        const std::unique_ptr<const GameLoop> GAME_LOOP;
    public: 
        Runtime();
        ~Runtime() = default;
};  