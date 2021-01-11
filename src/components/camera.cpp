#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const Transform transform, const float FOV, const float ratio, const float nearPlane, const float farPlane)
    : _FOV(std::move(FOV)), _ratio(std::move(ratio)), _nearPlane(std::move(nearPlane)), _farPlane(std::move(farPlane))
{
    this->transform = std::move(transform);
    _lookDir = glm::normalize(this->transform.getPosition() - glm::vec3(0.0f, 0.0f, -1.0f));

    _projMatrix = glm::perspective(glm::radians(FOV), ratio, nearPlane, farPlane);

    _viewMatrix = glm::mat4(1.0f);
    // _viewMatrix = glm::lookAt(transform.position, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    _viewMatrix = glm::inverse(this->transform.CalculateModelMatrix());
}
Camera::~Camera(){}