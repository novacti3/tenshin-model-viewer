#pragma once

#include "../core/types.hpp"
#include "shader.hpp"

#include <glm/vec3.hpp>

#include <array>

class Quad
{
    std::array<Vertex, 4> _vertices;
    std::array<unsigned char, 2*3> _indices;
    unsigned int _VAO, _VBO, _EBO;

    public:
    Quad(): _VAO(0), _VBO(0), _EBO(0)
    {}
    Quad(const glm::vec3 bottomLeft, const glm::vec3 topLeft, const glm::vec3 bottomRight, const glm::vec3 topRight);
    ~Quad();

    void Draw(Shader &shader);
};