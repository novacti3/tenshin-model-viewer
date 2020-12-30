#pragma once

#include <glm/vec2.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
    private:
    glm::uvec2 _size;
    std::string _title;
    GLFWwindow *_handle;

    public:
    Window(){}
    ~Window(){}

    public:
    bool Init(const glm::uvec2 size, const std::string title);
    void Cleanup();

    inline glm::uvec2  &getSize()   { return _size; }
    inline std::string &getTitle()  { return _title; }
    inline GLFWwindow  *getHandle() { return _handle; }
};