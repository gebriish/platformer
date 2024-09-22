#pragma once

#include <iostream>
#include "types.h"

struct GLFWwindow;

namespace ENGINE::INPUT {
	bool IsKeyPressed(int keycode);
	bool IsMouseButtonPressed(int keycode);

	std::pair<f32, f32> GetCursorPosition();
}