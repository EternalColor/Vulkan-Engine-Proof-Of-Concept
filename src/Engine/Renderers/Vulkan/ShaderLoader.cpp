#include "ShaderLoader.hpp"

namespace SnowfallEngine
{
    namespace Renderers
    {
        namespace VulkanRenderer
        {
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
            //size_t fileSize will be assigned and returned via reference
            std::unique_ptr<const uint32_t[]> ShaderLoader::readFile(const std::string& fileName, size_t& fileSize) const
            {
                //Set carret at end of file, so we can tell its size 
                std::ifstream file(fileName, std::ios::binary | std::ios::ate);

                if(file)
                {
                    fileSize = file.tellg();

                    char* fileBuffer = new char[fileSize];

                    //Reset carret and then read the whole file, we now know its size
                    file.seekg(0);
                    file.read(fileBuffer, fileSize);

                    file.close();

                    return std::unique_ptr<const uint32_t[]>
                    {
                        //Shader code is represented as uint32_t and not char so we cast the whole array
                        //Assuming the file is in uint32_t format so we dont need to recast every element. (This is standard SPIR-V behaviour)
                        reinterpret_cast<const uint32_t*>(fileBuffer)
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
                    size_t fileSize = 0;
                    const std::unique_ptr<const uint32_t[]> code = this->readFile(shaderPaths[i], fileSize);

                    shaderCreateInfo.codeSize = fileSize;
                    shaderCreateInfo.pCode = code.get();

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
        }
    }
}
