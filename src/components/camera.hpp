#pragma once

#include "transform.hpp"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
    public:
    Transform transform;

    private:
    glm::vec3 _lookDir;

    float _FOV, _ratio, _nearPlane, _farPlane;

    glm::mat4 _projMatrix = glm::mat4(1.0f);
    glm::mat4 _viewMatrix = glm::mat4(1.0f);

    public:
    Camera(const Transform transform, const float FOV, const float ratio, const float nearPlane, const float farPlane);
    ~Camera();

    inline const glm::mat4 getProjMatrix() const { return _projMatrix; }
    inline const glm::mat4 getViewMatrix() 
    {
        _viewMatrix = glm::inverse(transform.CalculateModelMatrix());
        return _viewMatrix; 
    }
};