#include <GLFW/glfw3.h>
#include "window.h"

int main()
{
    ENGINE::Window window(800, 500, "Delve");
    ENGINE::Window::Initialize(window);

    while(!glfwWindowShouldClose(window.GetContext()))
    {
        window.Update();
    }

    glfwDestroyWindow(window.GetContext());
}