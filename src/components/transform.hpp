#pragma once

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform(const glm::vec3 position = glm::vec3(0.0f), const glm::vec3 rotation = glm::vec3(0.0f), const glm::vec3 scale = glm::vec3(1.0f))
    {
        this->position = std::move(position);
        this->rotation = std::move(rotation);
        this->scale    = std::move(scale);
    }
    ~Transform(){}

    // TODO: Clamp rotation between 0-360

    glm::mat4 CalculateModelMatrix() const
    {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::scale(model, scale);
        // Yaw (Y axis)
        model = glm::rotate(model, glm::radians(rotation.y), GetWorldUpVector());
        // Roll (Z axis)
        model = glm::rotate(model, glm::radians(rotation.z), GetWorldForwardVector());
        // Pitch (X axis)
        model = glm::rotate(model, glm::radians(rotation.x), GetWorldRightVector());

        model = glm::translate(model, position);

        return model;
    }

    // glm::vec3 GetLocalForwardVector() const
    // {
    //     glm::vec3 vector = glm::vec3(0.0f);

    //     vector = glm::cross(GetWorldRightVector(), GetWorldUpVector());
    //     // Yaw (Y axis)
    //     vector = glm::rotateY(vector, glm::radians(rotation.y));
    //     // Roll (Z axis)
    //     vector = glm::rotateZ(vector, glm::radians(rotation.z));
    //     // Pitch (X axis)
    //     vector = glm::rotateX(vector, glm::radians(rotation.x));

    //     return -glm::normalize(vector);
    // }
    inline glm::vec3 GetWorldForwardVector() const { return glm::vec3(0.0f, 0.0f, -1.0f); }
    // TODO: Get right vector
    inline glm::vec3 GetWorldRightVector() const { return glm::vec3(1.0f, 0.0f, 0.0f); }
    // TODO: Get up vector
    inline glm::vec3 GetWorldUpVector() const { return glm::vec3(0.0f, 1.0f, 0.0f); }
};