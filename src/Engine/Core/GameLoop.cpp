#include "GameLoop.hpp"

namespace SnowfallEngine
{
    namespace Core
    {
        GameLoop::GameLoop() : renderWrapper { std::make_unique<Renderers::VulkanRenderer::VulkanWrapper>() }
        {

        }

        void GameLoop::Run() const
        {
            while(!this->renderWrapper->WINDOW->CloseRequested())
            {
                this->renderWrapper->WINDOW->PollEvents();
                this->renderWrapper->WINDOW->RenderOneFrame
                (
                    this->renderWrapper->DEVICE_FACTORY->DEVICE.get(), 
                    this->renderWrapper->DEVICE_FACTORY->DEVICE_QUEUE.get(), 
                    this->renderWrapper->SWAPCHAIN_FACTORY->SWAPCHAIN.get(), 
                    this->renderWrapper->SEMAPHORE_FACTORY->SEMAPHORE_IMAGE_AVAILABLE.get(), 
                    this->renderWrapper->SEMAPHORE_FACTORY->SEMAPHORE_RENDERING_DONE.get(), 
                    this->renderWrapper->COMMAND_BUFFER_FACTORY->BUFFER_COUNT, 
                    this->renderWrapper->COMMAND_BUFFER_FACTORY->BUFFERS.get()
                );
            }

            //Wait until all operation on the device has finished
            vkDeviceWaitIdle(*this->renderWrapper->DEVICE_FACTORY->DEVICE);
        }
    }
}