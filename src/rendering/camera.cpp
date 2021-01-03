#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
    _projMatrix = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
    
    _viewMatrix = glm::mat4(1.0f);
    _viewMatrix = glm::translate(_viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
}
Camera::~Camera(){}