#pragma once

#include "shader.hpp"
#include "model.hpp"

#include <unordered_map>
#include <string>

class ResourceManager final
{
    private:
    static std::unordered_map<std::string, Shader*> _loadedShaders;
    static std::unordered_map<std::string, Model*> _loadedModels;

    private:
    ResourceManager(){}
    ~ResourceManager(){}

    public:
    static void Cleanup();

    static Shader *CreateShaderFromFiles(const std::string &vertShaderPath, const std::string &fragShaderPath);
    static Shader *GetShader(const std::string &name);
    static void AddShader(Shader *shader, std::string name);

    static Model *CreateModelFromOBJFile(const std::string &filePath);
    static Model *GetModel(const std::string &name);
    static void AddModel(Model *model, std::string name);
};