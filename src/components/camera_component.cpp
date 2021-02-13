#include "components/camera_component.hpp"

#include <glm/gtc/matrix_transform.hpp>

CameraComponent::CameraComponent(const TransformComponent &initTransform, const float FOV, const float ratio, const float nearPlane, const float farPlane)
    : _FOV(std::move(FOV)), _ratio(std::move(ratio)), _nearPlane(std::move(nearPlane)), _farPlane(std::move(farPlane))
{
    _lookDir = glm::normalize(initTransform.getPosition() - glm::vec3(0.0f, 0.0f, -1.0f));

    _projMatrix = glm::perspective(glm::radians(FOV), ratio, nearPlane, farPlane);

    _viewMatrix = glm::mat4(1.0f);
    _viewMatrix = glm::inverse(initTransform.CalculateModelMatrix());
}
CameraComponent::~CameraComponent(){}