#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
    private:
    glm::mat4 _projMatrix = glm::mat4(1.0f);
    glm::mat4 _viewMatrix = glm::mat4(1.0f);

    glm::vec3 _pos = glm::vec3(0.0f);
    glm::vec3 _target = glm::vec3(0.0f);
    glm::vec3 _lookDir;
    glm::vec3 _camRight;
    glm::vec3 _camUp;

    public:
    Camera();
    ~Camera();

    void UpdatePos(float deltaTime);

    inline glm::mat4 &getProjMatrix() { return _projMatrix; }
    inline glm::mat4 &getViewMatrix() { return _viewMatrix; }
};