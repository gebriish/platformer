#include "window.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace ENGINE
{
	static bool s_GlfwInitialize = false;

	Window::Window(u16 width = 1280,
		u16 height = 800,
		const std::string& title = "Window")

		: m_WindowData({width, height, title})
	{}

	Window::~Window()
	{	
	}

	void Window::SetContext(GLFWwindow* window) 
		{ m_WindowData.glfwWindow = window; }

	void Window::Initialize(Window& window)
	{
		if(!s_GlfwInitialize) {

			if(!glfwInit()) {
				std::cout << "Failed to initialize glfw\n";
				exit(EXIT_FAILURE);
			}

			s_GlfwInitialize = true;
		}

 		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

		window.SetContext(glfwCreateWindow(window.GetWidth(), window.GetHeight(), window.GetTitle().c_str(), NULL, NULL));
		if(window.GetContext() == NULL) {
			std::cout << "Failed to create glfwWindow\n";
			exit(EXIT_FAILURE);
		}
		glfwMakeContextCurrent(window.GetContext());
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(this->GetContext());
	}
}