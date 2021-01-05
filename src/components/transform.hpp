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
    inline glm::vec3 GetWorldForwardVector() { return glm::vec3(0.0f, 0.0f, -1.0f); }
    // TODO: Get right vector
    inline glm::vec3 GetWorldRightVector() { return glm::vec3(1.0f, 0.0f, 0.0f); }
    // TODO: Get up vector
    inline glm::vec3 GetWorldUpVector() { return glm::vec3(0.0f, 1.0f, 0.0f); }
};