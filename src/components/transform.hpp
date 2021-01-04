#pragma once

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

struct Transform
{
    glm::vec3 position;
    // TODO: Add rotation
    glm::vec3 scale;

    Transform()
    {
        this->position = glm::vec3(0.0f);
        this->scale    = glm::vec3(1.0f);
    }
    Transform(glm::vec3 position, glm::vec3 scale = glm::vec3(1.0f))
    {
        this->position = position;
        this->scale    = scale;
    }
    ~Transform(){}

    // TODO: Get forward vector
    // TODO: Get right vector
    // TODO: Get up vector
};