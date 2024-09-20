#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window.h"

int main()
{
    ENGINE::Window window(800, 500, "Delve");
    ENGINE::Window::Initialize(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    


    while(!glfwWindowShouldClose(window.GetContext()))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        window.Update();
    }

    glfwDestroyWindow(window.GetContext());
}