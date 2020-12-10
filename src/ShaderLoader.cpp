#include "ShaderLoader.hpp"

ShaderLoader::ShaderLoader(const VkDevice* device, const std::vector<std::string>& vertexShaderPaths, const std::vector<std::string>& fragmentShaderPaths)
    :   //INITIALIZATION ORDER MATTERS
        CACHED_DEVICE { device },
        //The amount of shader is the same as the amount of paths of the corresponding shader category
        VERTEX_SHADER_COUNT { vertexShaderPaths.size() },
        FRAGMENT_SHADER_COUNT { fragmentShaderPaths.size() },
        VERTEX_SHADERS { this->createShaderModules(this->CACHED_DEVICE, vertexShaderPaths) },
        FRAGMENT_SHADERS { this->createShaderModules(this->CACHED_DEVICE, fragmentShaderPaths) }
{

}

ShaderLoader::~ShaderLoader()
{
    this->DestroyShaderModulesOfShaderCategory(this->VERTEX_SHADERS.get(), this->VERTEX_SHADER_COUNT);
    this->DestroyShaderModulesOfShaderCategory(this->FRAGMENT_SHADERS.get(), this->FRAGMENT_SHADER_COUNT);
}

//Shader Code is interpreted as uint32_t
std::unique_ptr<const std::vector<uint32_t>> ShaderLoader::readFile(const std::string& fileName) const
{
    //Set carret at end of file, so we can tell its size 
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);

    if(file)
    {
        size_t fileSize = file.tellg();
        //Heap allocation happens here but it MUST be assigned to a smart pointer afterwards
        std::vector<char>* fileBuffer = new std::vector<char>(fileSize);

        //Reset carret and then read the whole file, we now know its size
        file.seekg(0);
        file.read(fileBuffer->data(), fileSize);

        file.close();

        return std::unique_ptr<const std::vector<uint32_t>>
        {
            //Shader Code is interpreted as uint32_t
            reinterpret_cast<const std::vector<uint32_t> *>(fileBuffer)
        };
    }
    else
    {
        throw std::runtime_error("Failed to open file!");
    }
}

std::unique_ptr<const VkShaderModule[]> ShaderLoader::createShaderModules(const VkDevice* device, const std::vector<std::string>& shaderPaths) const
{
    //Catch case when no shader path was specified
    if(shaderPaths.size() == 0)
    {
        return nullptr;
    }

    VkShaderModuleCreateInfo shaderCreateInfo = {};
    shaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderCreateInfo.pNext = nullptr;
    shaderCreateInfo.flags = 0;

    std::unique_ptr<VkShaderModule[]> shaderModules = std::make_unique<VkShaderModule[]>(shaderPaths.size());

    for(uint32_t i = 0; i < shaderPaths.size(); ++i)
    {
        const std::unique_ptr<const std::vector<uint32_t>> code = this->readFile(shaderPaths[i]);

        shaderCreateInfo.codeSize = code.get()->size();
        shaderCreateInfo.pCode = code.get()->data();

        vkCreateShaderModule(*device, &shaderCreateInfo, nullptr, &shaderModules[i]);
    }

    return shaderModules;
}

void ShaderLoader::DestroyShaderModulesOfShaderCategory(const VkShaderModule shaderModules[], const uint32_t& shaderCount) const
{
    for(uint32_t currentShaderCount = 0; currentShaderCount < shaderCount; ++currentShaderCount)
    {
        vkDestroyShaderModule(*this->CACHED_DEVICE, shaderModules[currentShaderCount], nullptr);
    }
}