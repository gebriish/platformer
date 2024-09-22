#include "input.h"
#include <GLFW/glfw3.h>
#include "window.h"

namespace ENGINE::INPUT
{
	bool IsKeyPressed(int keycode)
	{
		int state = glfwGetKey(CORE::Window::Get().GetContext(), keycode);
		return state == GLFW_PRESS;
	}

	bool IsMouseButtonPressed(int buttoncode)
	{
		int state = glfwGetMouseButton(CORE::Window::Get().GetContext(), buttoncode);
		return state == GLFW_PRESS;
	}

	std::pair<f32, f32> GetCursorPosition()
	{
		f64 xpos, ypos;
		glfwGetCursorPos(CORE::Window::Get().GetContext(), &xpos, &ypos);

		return { f32(xpos), f32(ypos) };
	}

}