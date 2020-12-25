#include "window.hpp"

bool Window::Init(const unsigned int width, const unsigned int height, const std::string title)
{
    _width = width;
    _height = height;
    _title = title;

    if(!glfwInit())
    {
        return false;
    }

    // TODO: Hints

    _handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(_handle);

    // TODO: glad init

    return true;
}

void Window::Cleanup()
{
    glfwDestroyWindow(_handle);
    glfwTerminate();
}

unsigned int Window::getWidth() { return _width; }
unsigned int Window::getHeight() { return _height; }
std::string Window::getTitle() { return _title; }
GLFWwindow *Window::getHandle() {return _handle; }