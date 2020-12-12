#include "ViewportFactory.hpp"

ViewportFactory::ViewportFactory(const uint32_t& windowWidth, const uint32_t& windowHeight)
    :   //INITIALIZATION ORDER MATTERS
        VIEWPORT 
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
        },
        SCISSOR 
        { 
            new VkRect2D
            {
                VkOffset2D{ 0, 0 },                     //offset
                VkExtent2D{ windowWidth, windowHeight } //extend
            } 
        }
{

}