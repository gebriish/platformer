#include "application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <core/logger.h>


Application* Application::s_Instance = nullptr;
float deltaTime = 0.0;


Application::Application(const char* title, uint16_t width, uint16_t height, int window_flags)
{
	s_Instance = this;

	m_Window.title = title;
	m_Window.width  = width;
	m_Window.height = height;

	initialize_window(m_Window, window_flags);
	set_event_callback(m_Window, std::bind(&Application::dispatch_event, this, std::placeholders::_1));

#ifdef DEBUG
	Logger::log(LogLevel::INFO, "Application created [\'%s\', %d, %d]", title, width, height);
#endif
}

Application::~Application()
{
	m_LayerManager.cleanup();
	destroy_window(m_Window);

#ifdef DEBUG
	Logger::log(LogLevel::INFO, "Application close");
#endif
}

void Application::run()
{
	float begin_time = (float)glfwGetTime();

	while(!window_should_close(m_Window))
	{		
		float end_time = (float) glfwGetTime();
		deltaTime = end_time - begin_time;
		begin_time = end_time;
		
		this->update(deltaTime);

		swap_buffer(m_Window);
	}
}

uint64_t Application::framerate() const
{
	return uint64_t(1/deltaTime);
}


void Application::dispatch_event(Event& e)
{
	m_LayerManager.dispatchEvent(e);
}

void Application::update(float dt)
{
	m_LayerManager.callUpdate(dt);
}
