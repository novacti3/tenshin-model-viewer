#include "resource_manager.hpp"

#include "log.hpp"

#include <fstream>
#include <sstream>

std::unordered_map<std::string, Shader*> ResourceManager::_loadedShaders;

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


Shader *ResourceManager::CreateShaderFromFiles(const std::string &vertShaderPath, const std::string &fragShaderPath)
{
    std::ifstream vertShaderFile(vertShaderPath), fragShaderFile(fragShaderPath);
    std::stringstream vertShaderSourceStream, fragShaderSourceStream;
    std::string vertShaderSource, fragShaderSource;
    
    // Read the vertex shader file at the provided file path and store its contents
    if(vertShaderFile.is_open())
    {
        vertShaderSourceStream << vertShaderFile.rdbuf();
    }
    else
    {
        Log::LogError("Couldn't open file " + vertShaderPath);
        return nullptr;
    }
    vertShaderFile.close();
    
    // Read the fragment shader file at the provided file path and store its contents
    if(fragShaderFile.is_open())
    {
        fragShaderSourceStream << fragShaderFile.rdbuf();
    }
    else
    {
        Log::LogError("Couldn't open file " + fragShaderPath);
        return nullptr;
    }
    fragShaderFile.close();
    vertShaderSource = vertShaderSourceStream.str();
    fragShaderSource = fragShaderSourceStream.str();
    
    // Create a new shader from the extracted sources
    Shader *shader = new Shader();
    shader->Init(vertShaderSource.c_str(), fragShaderSource.c_str());
    
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

    Log::LogError("Couldn't find shader " + name);
    return nullptr;
}

void ResourceManager::AddShader(Shader *shader, std::string name)
{
    _loadedShaders.insert(std::make_pair(name, shader));
}