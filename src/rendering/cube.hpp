#pragma once

#include "../core/types.hpp"
#include "shader.hpp"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <array>

class Cube
{
    std::array<Vertex, 36> _vertices;
    unsigned int _VAO, _VBO;

    public:
    Cube();
    ~Cube();

    void Draw(Shader &shader, const float rot, const glm::mat4 &viewMatrix, const glm::mat4 &projMatrix);
};