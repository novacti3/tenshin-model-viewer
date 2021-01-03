#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
    _projMatrix = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
    
    _pos = glm::vec3(0.0f, 0.0f, 3.0f);
    _target = glm::vec3(0.0f);
    _lookDir = glm::normalize(_pos - _target);

    _camRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), _lookDir));
    _camUp = glm::normalize(glm::cross(_lookDir, _camRight));
    
    _viewMatrix = glm::lookAt(_pos, _target, glm::vec3(0.0f, 1.0f, 0.0f));
}
Camera::~Camera(){}

void Camera::UpdatePos(float deltaTime)
{
    float camX = sin(deltaTime) * 5.0f;
    float camZ = cos(deltaTime) * 5.0f;

    _pos = glm::vec3(camX, 0.0f, camZ);

    _viewMatrix = glm::lookAt(_pos, _target, glm::vec3(0.0f, 1.0f, 0.0f));
}