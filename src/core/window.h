#pragma once

#include <types.h>
#include <string>
#include <functional>

struct GLFWwindow;

namespace ENGINE::CORE {

	struct Event;

	class Window
	{
		using EventCallbackFn = std::function<void(Event&)>;

	public:
		Window(u16 width, u16 height, const std::string& title);
		~Window();

		static void Initialize(Window& window);

		void Update();
		void SetContext(GLFWwindow* window);

		inline u16 GetWidth() const { return m_WindowData.width; }
		inline u16 GetHeight() const { return m_WindowData.height; }
		inline std::string GetTitle() const { return m_WindowData.title; }
		inline GLFWwindow* GetContext() const { return m_WindowData.glfwWindow; }

		void SetEventCallback(const EventCallbackFn& callback);

	private:
		void setWindowUserPointer();

	private:
		struct WindowData{

			u16 width;
			u16 height;
			std::string title;
			GLFWwindow* glfwWindow = nullptr;

			EventCallbackFn EventCallback;

		} m_WindowData;
	};
}
