#pragma once

#include <glm/mat4x4.hpp>

class Camera
{
    private:
    glm::mat4 _projMatrix = glm::mat4(1.0f);
    glm::mat4 _viewMatrix = glm::mat4(1.0f);

    public:
    Camera();
    ~Camera();

    inline glm::mat4 &getProjMatrix() { return _projMatrix; }
    inline glm::mat4 &getViewMatrix() { return _viewMatrix; }
};