#include "resource_manager.hpp"

#include "core/log.hpp"
#include "core/utils.hpp"

#include <fstream>
#include <sstream>

void ResourceManager::Cleanup()
{
    // Delete all loaded shaders
    for(auto shader: _loadedShaders)
    {
        delete shader.second;
        shader.second = nullptr;
    }
    _loadedShaders.clear();
}

#pragma region Shaders
    Shader *ResourceManager::CreateShaderFromFiles(const std::string &vertShaderPath, const std::string &fragShaderPath)
    {
        // NOTE: Might want to wrap this in a try-catch block
        std::ifstream vertShaderFile(vertShaderPath), fragShaderFile(fragShaderPath);
        std::stringstream vertShaderSourceStream, fragShaderSourceStream;
        std::string vertShaderSource, fragShaderSource;
        
        // Read the vertex shader file at the provided file path and store its contents
        if(!vertShaderFile.is_open())
        {
            Log::LogError("Couldn't open file " + vertShaderPath);
            return nullptr;
        }
        
        vertShaderSourceStream << vertShaderFile.rdbuf();
        vertShaderFile.close();
        
        // Read the fragment shader file at the provided file path and store its contents
        if(!fragShaderFile.is_open())
        {
            Log::LogError("Couldn't open file " + fragShaderPath);
            return nullptr;
        }

        fragShaderSourceStream << fragShaderFile.rdbuf();
        fragShaderFile.close();
        
        vertShaderSource = vertShaderSourceStream.str();
        fragShaderSource = fragShaderSourceStream.str();
        
        // Create a new shader from the extracted sources
        Shader *shader = new Shader(vertShaderSource.c_str(), fragShaderSource.c_str());
        return shader;
    }

    Shader *ResourceManager::GetShader(const std::string &name)
    {
        for(auto shader: _loadedShaders)
        {
            if(shader.first.compare(name) == 0)
            {
                return shader.second;
            }
        }
        Log::LogError("Couldn't find shader " + name + " among loaded shaders");
        return nullptr;
    }

    void ResourceManager::AddShader(Shader *shader, std::string name)
    {
        _loadedShaders.insert(std::make_pair(name, shader));
    }
#pragma endregion
