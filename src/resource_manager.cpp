#include "resource_manager.hpp"

#include "log.hpp"
#include "utils.hpp"

#include <fstream>
#include <sstream>

std::unordered_map<std::string, Shader*> ResourceManager::_loadedShaders;
std::unordered_map<std::string, Model*> ResourceManager::_loadedModels;

void ResourceManager::Cleanup()
{
    // Delete all loaded shaders
    for(auto shader: _loadedShaders)
    {
        delete shader.second;
        shader.second = nullptr;
    }
    _loadedShaders.clear();

    // Delete all loaded models
    for(auto model: _loadedModels)
    {
        delete model.second;
        model.second = nullptr;
    }
    _loadedModels.clear();
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
        Log::LogError("Couldn't find shader " + name + " among loaded shaders");
        return nullptr;
    }

    void ResourceManager::AddShader(Shader *shader, std::string name)
    {
        _loadedShaders.insert(std::make_pair(name, shader));
    }
#pragma endregion

#pragma region Models

    Model *ResourceManager::CreateModelFromOBJFile(const std::string &filePath)
    {
        std::vector<Vertex> vertices;
        std::vector<Face> faces;

        // NOTE: Might want to wrap this in a try-catch block
        std::ifstream file(filePath);

        if(!file.is_open())
        {
            Log::LogError("Couldn't open file " + filePath);
            return nullptr;
        }

        std::string line;
        std::vector<std::string> splitLine;
        unsigned int vtCounter = 0;
        unsigned int vnCounter = 0;
        while(std::getline(file, line))
        {
            splitLine = SplitString(line, ' ');
            
            if(line[0] == '#')
            {
                continue;
            }
            else if(line[0] == 'v')
            {
                if(line[1] == ' ')
                {
                    Vertex vert;
                    vert.position = glm::vec3(std::stof(splitLine[1]), std::stof(splitLine[2]), std::stof(splitLine[3]));

                    vertices.push_back(vert);
                }
                else if(line[1] == 't')
                {
                    vertices[vtCounter].uv = glm::vec2(std::stof(splitLine[1]), std::stof(splitLine[2]));

                    vtCounter++;
                }
                else if(line[1] == 'n')
                {
                    vertices[vnCounter].normal = glm::vec3(std::stof(splitLine[1]), std::stof(splitLine[2]), std::stof(splitLine[3]));

                    vnCounter++;
                }
            }

            // TODO: Add face parsing
        }
        
        Model *model = new Model(std::move(vertices), std::move(faces));
        return model;
    }

    Model *ResourceManager::GetModel(const std::string &name)
    {
        for(auto model: _loadedModels)
        {
            if(model.first.compare(name) == 0)
            {
                return model.second;
            }
        }
        Log::LogError("Couldn't find model " + name + " among loaded models");
        return nullptr;
    }

    void ResourceManager::AddModel(Model *model, std::string name)
    {
        _loadedModels.insert(std::make_pair(name, model));
    }

#pragma endregion