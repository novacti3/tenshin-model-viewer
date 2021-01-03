#pragma once

#include <glm/vec2.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <functional>

class Window
{
    private:
    // NOTE: Read more about this shit.
    // Is it even necesarry when it's basically guaranteed that there will only be 1 app instance with 1 window?
    static std::function<void(int, int)> _onResize;
    glm::uvec2 _size;
    std::string _title;
    GLFWwindow *_handle;

    public:
    Window(){}
    ~Window(){}

    public:
    bool Init(glm::uvec2 size, const std::string title);
    void Cleanup();

    inline glm::uvec2  &getSize()   { return _size; }
    inline std::string &getTitle()  { return _title; }
    inline GLFWwindow  *getHandle() { return _handle; }

    static void ResizeCallback(GLFWwindow *window, int width, int height) { _onResize(width, height); }

    private:
    void OnResize(int width, int height);
};