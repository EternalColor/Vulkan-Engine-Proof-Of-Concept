#pragma once

#include <vector>

//TODO: Remove from release
class Layers final
{
    public:
        Layers();
        ~Layers() = default;
        
        //Read-only "getter fields"
        const std::vector<const char *> REQUIRED_LAYERS;
};
