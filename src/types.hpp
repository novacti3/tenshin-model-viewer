#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 uv;
    glm::ivec3 normal;

    Vertex()
    {
        this->position = glm::vec3(0.0f);
        this->uv = glm::vec2(0.0f);
        this->normal = glm::ivec3(0);
    }
    Vertex(glm::vec3 position, glm::vec2 uv, glm::ivec3 normal)
    {
        this->position = position;
        this->uv = uv;
        this->normal = normal;
    }
    ~Vertex(){}
};

struct Face
{
    glm::uvec3 firstTriangleIndices;
    glm::uvec3 secondTriangleIndices;

    Face()
    {
        this->firstTriangleIndices = glm::uvec3(0);
        this->secondTriangleIndices = glm::uvec3(0);
    }
    Face(glm::uvec3 firstTriangleIndices, glm::uvec3 secondTriangleIndices)
    {
        this->firstTriangleIndices = firstTriangleIndices;
        this->secondTriangleIndices = secondTriangleIndices;    
    }
    ~Face(){}
};