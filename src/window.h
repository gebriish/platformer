#ifndef WINDOW_H
#define WINDOW_H

#include <types.h>
#include <string>

struct GLFWwindow;

namespace ENGINE {

	class Window
	{
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

	private:
		struct {

			u16 width;
			u16 height;
			std::string title;
			GLFWwindow* glfwWindow = nullptr;

		} m_WindowData;
	};
}

#endif
