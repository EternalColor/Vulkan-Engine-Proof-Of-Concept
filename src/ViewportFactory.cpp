#include "ViewportFactory.hpp"

ViewportFactory::ViewportFactory(const uint32_t& windowWidth, const uint32_t& windowHeight)
    :   //INITIALIZATION ORDER MATTERS
        VIEWPORT { this->createViewport(windowWidth, windowHeight) },
        SCISSOR { this->createScissor(windowWidth, windowHeight) }
{

}

std::unique_ptr<const VkViewport> ViewportFactory::createViewport(const uint32_t& windowWidth, const uint32_t& windowHeight) const
{
    return std::unique_ptr<const VkViewport>
    {
        new VkViewport
        {
            0.0f,         //x
            0.0f,         //y
            windowWidth,  //width
            windowHeight, //height
            0.0f,         //minDepth
            1.0f          //maxDepth
        }
    };
}

std::unique_ptr<const VkRect2D> ViewportFactory::createScissor(const uint32_t& windowWidth, const uint32_t& windowHeight) const
{
    return std::unique_ptr<const VkRect2D>
    {
        new VkRect2D
        {
            VkOffset2D{ 0, 0 },                     //offset
            VkExtent2D{ windowWidth, windowHeight } //extend
        }
    };
}