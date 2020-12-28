#pragma once

#include "shader.hpp"
#include "model.hpp"

#include <glm/vec3.hpp>

class Renderer final
{
    private:
    unsigned int _VAO;
    unsigned int _VBO;
    
    private:
    Renderer(){}
    ~Renderer(){}

    public:
    static void DrawModel(Model *model, Shader *shader, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);
};