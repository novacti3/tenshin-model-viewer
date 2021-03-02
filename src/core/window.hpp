#pragma once

#include "core/singleton.hpp"
#include "core/event.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <string>
#include <functional>

class Window final : public Singleton<Window>, public EventSender
{
    friend class Singleton<Window>;

    private:
    glm::uvec2 _size;
    std::string _title;
    GLFWwindow *_handle;

    private:
    Window() = default;
    ~Window() = default;
    // Copy
    Window(const Window& other) = delete;
    Window& operator=(Window other) = delete;
    // Move
    Window(Window&& other) = delete;
    Window& operator=(Window&& other) = delete;

    public:
    bool Init(glm::uvec2 size, const std::string title);
    void Cleanup();

    inline const glm::uvec2    getSize() { return _size; }
    inline const std::string  getTitle() { return _title; }
    inline       GLFWwindow* getHandle() { return _handle; }

    private:
    inline void setSize(glm::uvec2 newSize) { _size = std::move(newSize); }
    static void ResizeCallback(GLFWwindow *window, int width, int height);
};