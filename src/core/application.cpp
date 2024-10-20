#include "application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Application* Application::s_Instance = nullptr;


Application::Application(const char* title, uint16_t width, uint16_t height, int window_flags)
{
	s_Instance = this;

	m_Window.title = title;
	m_Window.width  = width;
	m_Window.height = height;

	initialize_window(m_Window, window_flags);
	set_event_callback(m_Window, std::bind(&Application::onEvent, this, std::placeholders::_1));
}

Application::~Application()
{
	m_LayerManager.cleanup();
	destroy_window(m_Window);
}

void Application::run()
{
	float begin_time = (float)glfwGetTime();

	while(!window_should_close(m_Window))
	{

		
		float end_time = (float) glfwGetTime();
		float deltaTime = end_time - begin_time;
		begin_time = end_time;

		clear_viewport(color_from_hexcode("232323"));

		this->onUpdate(deltaTime);

		swap_buffer(m_Window);
	}
}

void Application::onEvent(Event& e)
{
	m_LayerManager.dispatchEvent(e);
}

void Application::onUpdate(float dt)
{
	m_LayerManager.callUpdate(dt);
}