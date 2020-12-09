#pragma once

#include <memory>
#include <vector>
#include <string>
#include "Layers.hpp"
#include "ApplicationFactory.hpp"
#include "InstanceFactory.hpp"
#include "PhysicalDeviceFactory.hpp"
#include "PhysicalDeviceQueueFactory.hpp"
#include "DeviceFactory.hpp"
#include "Window.hpp"
#include "SwapchainFactory.hpp"
#include "ShaderLoader.hpp"
#include "ViewportFactory.hpp"
#include "GameLoop.hpp"

class Runtime final
{
    private:
        //TODO: Load from folder
        const std::vector<std::string> VERTEX_SHADER_PATHS;
        const std::vector<std::string> FRAGMENT_SHADER_PATHS;

        //Read-only "getter fields"
        const std::unique_ptr<const Layers> LAYERS;
        const std::unique_ptr<const ApplicationFactory> APPLICATION_FACTORY;
        const std::unique_ptr<const InstanceFactory> INSTANCE_FACTORY;
        const std::unique_ptr<const PhysicalDeviceFactory> PHYSICAL_DEVICE_FACTORY;
        const std::unique_ptr<const PhysicalDeviceQueueFactory> PHYSICAL_DEVICE_QUEUE_FACTORY;
        const std::unique_ptr<const DeviceFactory> DEVICE_FACTORY;
        const std::unique_ptr<const Window> WINDOW;
        const std::unique_ptr<const SwapchainFactory> SWAPCHAIN_FACTORY;
        const std::unique_ptr<const ShaderLoader> SHADER_LOADER;
        const std::unique_ptr<const ViewportFactory> VIEWPORT_FACTORY;
        const std::unique_ptr<const GameLoop> GAME_LOOP;
    public: 
        Runtime();
        ~Runtime() = default;
};  