#pragma once
#include <cstdint>
#include <functional>
#include "../graphics/color.h"
#include "event.h"

struct GLFWwindow;

using EventCallbackFn = std::function<void(Event&)>;

enum WindowFlags 
{
	WINDOWFLAG_NONE      	= 0,
	WINDOWFLAG_MAXIMIZED 	= 1 << 0,
	WINDOWFLAG_RESIZABLE 	= 1 << 1,
	WINDOWFLAG_VSYNC     	= 1 << 2,
	WINDOWFLAG_UNDECORATED 	= 1 << 3,
};

struct Window
{
	uint16_t width  = 1280;
	uint16_t height = 800;
	const char* title = "untitled";
	GLFWwindow* glfwWindow;

	struct {
		double x, y;
	} cursor;

	EventCallbackFn EventCallback;
};

void set_event_callback(Window &window,const EventCallbackFn& callback);

void initialize_window(Window& window, int flags);
void close_window(Window& window);
void destroy_window(Window& window);

void clear_viewport(float, float, float, float);
void clear_viewport(const Color& color);
void set_render_region(int x, int y, int width, int height);
void swap_buffer(const Window& window);

bool window_should_close(const Window& window);