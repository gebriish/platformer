#include "window.h"

#include <GLFW/glfw3.h>
#include <iostream>

#include <core/event.h>

namespace ENGINE::CORE
{
	Window* Window::s_Instance = nullptr;
	static bool s_GlfwInitialize = false;

	Window::Window(u16 width,
		u16 height,
		const std::string& title)

		: m_WindowData({width, height, title})
	{
	}

	Window::~Window()
	{
	}

	void Window::SetContext(GLFWwindow* window) 
		{ m_GLFWwindow = window; }

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
		window.setWindowUserPointer();

		glfwSwapInterval(0);

		glfwSetFramebufferSizeCallback(window.GetContext(), [](GLFWwindow* event_window, int width, int height)
		{	
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(event_window);
			data.width = width;
			data.height = height;

			Event e = Event::CreateResizeEvent(width, height);
			data.EventCallback(e);
		});


		glfwSetKeyCallback(window.GetContext(), [](GLFWwindow* event_window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(event_window);
			
			Event e = Event::CreateKeyEvent(key, scancode, action, mods);
			data.EventCallback(e);

		});

		glfwSetCursorPosCallback(window.GetContext(), [](GLFWwindow* event_window, double xpos, double ypos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(event_window);

			Event e = Event::CreateCursorMoveEvent(xpos, ypos, xpos - data.cursorPosition.first, ypos - data.cursorPosition.second);
			data.EventCallback(e);

			data.cursorPosition.first  = xpos;
			data.cursorPosition.second = ypos;
		});

		glfwSetMouseButtonCallback(window.GetContext(), [](GLFWwindow* event_window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(event_window);

			Event e = Event::CreateMouseButtonEvent(button, action, mods);
			data.EventCallback(e);
		});

		/*
		glfwSetWindowCloseCallback(window.GetContext(), [](GLFWwindow* event_window){
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
		});
		*/

		Window::s_Instance = &window;

	}

	void Window::setWindowUserPointer() {
		glfwSetWindowUserPointer(GetContext(), &m_WindowData);
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(this->GetContext());
	}

	void Window::SetEventCallback(const EventCallbackFn& callback) 
	{
		m_WindowData.EventCallback = callback;
	}

}
