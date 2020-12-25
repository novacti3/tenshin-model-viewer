#include "window.hpp"
#include "app.hpp"

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const std::string WINDOW_TITLE = "Model Viewer";

int main()
{
    Window window;
    window.Init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    App app;
    app.Init(&window);

    float lastTime, currentTime, deltaTime;
    while(!glfwWindowShouldClose(window.getHandle()))
    {
        // NOTE: Might want to move this into a static Time class or something so it's accessible from anywhere
        currentTime = glfwGetTime() / 1000;
        deltaTime = currentTime - lastTime;
        lastTime = deltaTime;

        app.PollInput(deltaTime);
        app.Update(deltaTime);
    }

    app.Cleanup();

    return 0;
}