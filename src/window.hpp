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

    unsigned int getWidth();
    unsigned int getHeight();
    std::string getTitle();
    GLFWwindow *getHandle();
};