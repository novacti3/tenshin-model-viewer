#pragma once

#include "core/event.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <string>
#include <functional>

class Window final : public EventSender
{
    private:
    glm::uvec2 _size;
    std::string _title;
    GLFWwindow *_handle;

    // NOTE: Read more about this shit.
    // Is it even necesarry when it's basically guaranteed that there will only be 1 app instance with 1 window?
    static std::function<void(int, int)> _onResize;

    public:
    Window(){}
    ~Window(){}

    public:
    bool Init(glm::uvec2 size, const std::string title);
    void Cleanup();

    inline const glm::uvec2    getSize() const { return _size; }
    inline const std::string  getTitle() const { return _title; }
    inline       GLFWwindow* getHandle() const { return _handle; }

    // NOTE: Figure out how to tie this in with the window resize event of the event system
    static void ResizeCallback(GLFWwindow *window, int width, int height) { _onResize(width, height); }

    private:
    void OnResize(int width, int height);
};