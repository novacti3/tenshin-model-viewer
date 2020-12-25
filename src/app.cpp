#include "app.hpp"

#include <GLFW/glfw3.h>

void App::Init(Window *window)
{
    _window = window;
}

void App::PollInput(float deltaTime)
{

}

void App::Update(float deltaTime)
{
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f, 0.0f, 0.2f, 1.0f);

    glfwSwapBuffers(_window->getHandle());
}

void App::Cleanup()
{
    _window->Cleanup();
    delete _window;
    _window = 0;
}