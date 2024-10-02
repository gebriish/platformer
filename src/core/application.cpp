#include "application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace ENGINE::CORE
{

	Application::Application()
	{
		Window::Initialize(MainWindow);
		
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			exit(EXIT_FAILURE);
		}    

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		MainWindow.SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{
		glfwDestroyWindow(MainWindow.GetContext());
		glfwTerminate();
	}

	void Application::Run()
	{
		this->Init();

		f32 lastFrameTime = (f32) glfwGetTime();

		while(!glfwWindowShouldClose(MainWindow.GetContext()))
		{
			f32 time = (f32) glfwGetTime();
			float dt = time - lastFrameTime;
			lastFrameTime = time;

			this->Update(dt);

			MainWindow.Update();
		}

		this->Cleanup();

	}
}
