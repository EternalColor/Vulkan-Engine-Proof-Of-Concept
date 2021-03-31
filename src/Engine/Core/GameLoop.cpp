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
            //Delta Time is the time since last frame
            double deltaTime = 0.0f;
            while(!this->renderWrapper->WINDOW->CloseRequested())
            { 
                //!IMPORTANT! messuring timeBeforeRendering and calling the Render method must be executed in this order
                std::chrono::high_resolution_clock::time_point timeBeforeRendering = std::chrono::high_resolution_clock::now();
                this->Render();
                
                //!IMPORTANT! messuring deltaTime and calling Tick must be executed in this order
                //now - timeBeforeRendering = deltaTime (Time the rendering took)
                deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - timeBeforeRendering).count();

                std::cout << "FPS: " << 1 / deltaTime << '\n';

                this->Tick(deltaTime);
            }

            //Wait until all operation on the device have finished
            vkDeviceWaitIdle(*this->renderWrapper->DEVICE_FACTORY->DEVICE);
        }

        void GameLoop::Render() const
        {
            this->renderWrapper->WINDOW->RenderOneFrame
            (
                this->renderWrapper->DEVICE_FACTORY->DEVICE.get(), 
                this->renderWrapper->DEVICE_FACTORY->QUEUE.get(), 
                this->renderWrapper->SWAPCHAIN_FACTORY->SWAPCHAIN.get(), 
                this->renderWrapper->SEMAPHORE_FACTORY->IMAGE_AVAILABLE.get(), 
                this->renderWrapper->SEMAPHORE_FACTORY->RENDERING_DONE.get(), 
                this->renderWrapper->COMMAND_BUFFER_FACTORY->BUFFER_COUNT, 
                this->renderWrapper->COMMAND_BUFFER_FACTORY->BUFFERS.get()
            );
        }

        void GameLoop::Tick(const float& deltaTime) const
        {
            this->renderWrapper->WINDOW->PollEvents();
        }
    }
}
