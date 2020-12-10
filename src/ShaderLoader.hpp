#pragma once

#include <vulkan/vulkan.h>
#include <algorithm>
#include <memory>
#include <vector>
#include <string>
#include <fstream>

class ShaderLoader final
{
    private:
        //Read only, no smart pointer required
        const VkDevice* CACHED_DEVICE;
        std::unique_ptr<const uint32_t[]> readFile(const std::string& fileName, size_t& fileSize) const;
        std::unique_ptr<const VkShaderModule[]> createShaderModules(const VkDevice* device, const std::vector<std::string>& shaderPaths) const;
        void DestroyShaderModulesOfShaderCategory(const VkShaderModule shaderModules[], const uint32_t& shaderCount) const;
    public: 
        ShaderLoader(const VkDevice* device, const std::vector<std::string>& vertexShaderPaths, const std::vector<std::string>& fragmentShaderPaths);
        ~ShaderLoader();

        //Read-only "getter fields"
        const size_t VERTEX_SHADER_COUNT;
        const size_t FRAGMENT_SHADER_COUNT;

        const std::unique_ptr<const VkShaderModule[]> VERTEX_SHADERS;
        const std::unique_ptr<const VkShaderModule[]> FRAGMENT_SHADERS;
};