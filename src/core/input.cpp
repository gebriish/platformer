#include "input.h"
#include <GLFW/glfw3.h>
#include "application.h"


bool Input::isKeyPressed(int keycode)
{
	auto& window = Application::Get().window();
	return glfwGetKey(window.glfwWindow, keycode) == GLFW_PRESS;
}

bool Input::isMouseButtonPressed(int button)
{
	auto& window = Application::Get().window();
	return glfwGetMouseButton(window.glfwWindow, button) == GLFW_PRESS;
}

std::pair<float,float> Input::getCursorPosition()
{
	double x, y;
	auto& window = Application::Get().window();
	glfwGetCursorPos(window.glfwWindow, &x, &y);
	return std::pair<float,float>{(float)x, window.height - (float(y))};
}

void Input::setCursorMode(CursorMode mode)
{

	auto glfwWindow = Application::Get().window().glfwWindow;

	switch (mode)
	{
		case CursorMode::CAPTURED:
			glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);		
		break;
		case CursorMode::DISABLED:
			glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			break;
		case CursorMode::HIDDEN:
			glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			break;
		case CursorMode::NORMAL:
			glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
	}
}