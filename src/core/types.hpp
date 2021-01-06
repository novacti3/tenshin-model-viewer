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
        this->position = std::move(position);
        this->uv = std::move(uv);
        this->normal = std::move(normal);
    }
    ~Vertex(){}
};