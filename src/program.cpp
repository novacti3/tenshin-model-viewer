#include "window.hpp"

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const std::string WINDOW_TITLE = "Model Viewer";

int main()
{
    Window window;
    window.Init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    while(!glfwWindowShouldClose(window.getHandle()))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.0f, 0.2f, 1.0f);

        glfwSwapBuffers(window.getHandle());
    }

    window.Cleanup();

    return 0;
}