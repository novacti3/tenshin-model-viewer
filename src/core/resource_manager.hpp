#pragma once

#include "../rendering/shader.hpp"

#include <unordered_map>
#include <string>

class ResourceManager final
{
    private:
    static std::unordered_map<std::string, Shader*> _loadedShaders;

    private:
    ResourceManager(){}
    ~ResourceManager(){}

    public:
    static void Cleanup();

    static Shader *CreateShaderFromFiles(const std::string &vertShaderPath, const std::string &fragShaderPath);
    static Shader *GetShader(const std::string &name);
    static void AddShader(Shader *shader, std::string name);
};