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
    static glm::uvec2 _size;
    static std::string _title;
    static GLFWwindow *_handle;

    private:
    Window(){}
    ~Window(){}

    public:
    static bool Init(glm::uvec2 size, const std::string title);
    static void Cleanup();

    static inline const glm::uvec2    getSize() { return _size; }
    static inline const std::string  getTitle() { return _title; }
    static inline       GLFWwindow* getHandle() { return _handle; }

    private:
    static void ResizeCallback(GLFWwindow *window, int width, int height);
};