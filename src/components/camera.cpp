#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const Transform transform, const float FOV, const float ratio, const float nearPlane, const float farPlane)
    : _FOV(FOV), _ratio(ratio), _nearPlane(nearPlane), _farPlane(farPlane)
{
    this->transform = transform;
    _lookDir = glm::normalize(transform.position - glm::vec3(0.0f, 0.0f, -1.0f));

    _projMatrix = glm::perspective(glm::radians(FOV), ratio, nearPlane, farPlane);

    _viewMatrix = glm::mat4(1.0f);
    _viewMatrix = glm::lookAt(transform.position, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
Camera::~Camera(){}

void Camera::LookAt(const glm::vec3 &target)
{
    _viewMatrix = glm::lookAt(transform.position, target, glm::vec3(0.0f, 1.0f, 0.0f));
}