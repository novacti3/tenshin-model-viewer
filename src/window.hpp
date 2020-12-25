#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
    private:
    unsigned int _width, _height;
    std::string _title;
    GLFWwindow *_handle;

    public:
    Window(){}
    ~Window(){}

    public:
    bool Init(const unsigned int width, const unsigned int height, const std::string title);
    void Cleanup();

    inline unsigned int getWidth() { return _width; }
    inline unsigned int getHeight() { return _height; }
    inline std::string getTitle() { return _title; }
    inline GLFWwindow *getHandle() { return _handle; }
};