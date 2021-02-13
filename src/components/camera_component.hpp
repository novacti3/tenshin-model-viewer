#pragma once

#include "components/icomponent.hpp"
#include "components/transform_component.hpp"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class CameraComponent final : public IComponent
{
    private:
    glm::vec3 _lookDir;

    float _FOV, _ratio, _nearPlane, _farPlane;

    glm::mat4 _projMatrix = glm::mat4(1.0f);
    glm::mat4 _viewMatrix = glm::mat4(1.0f);

    public:
    CameraComponent(const TransformComponent &initTransform, const float FOV, const float ratio, const float nearPlane, const float farPlane);
    ~CameraComponent();

    inline const glm::mat4 getProjMatrix() const { return _projMatrix; }
    inline const glm::mat4 getViewMatrix(const TransformComponent &transform) 
    {
        _viewMatrix = glm::inverse(transform.CalculateModelMatrix());
        return _viewMatrix; 
    }
};