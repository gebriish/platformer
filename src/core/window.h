#pragma once

#include <types.h>
#include <string>
#include <functional>

struct GLFWwindow;

namespace ENGINE::CORE {	
	
	struct Event;
	struct WindowData;

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
		inline GLFWwindow* GetContext() const { return m_GLFWwindow; }

		void SetEventCallback(const EventCallbackFn& callback);


		static inline Window& Get() { return *s_Instance; } 

	private:
		void setWindowUserPointer();

	private:
		struct WindowData{	
			using EventCallbackFn = std::function<void(Event&)>;

			u16 width;
			u16 height;
			std::string title;

			EventCallbackFn EventCallback;

			std::pair<f64, f64> cursorPosition;

		} m_WindowData;	
		
		GLFWwindow* m_GLFWwindow = nullptr;


	private:
		static Window* s_Instance;
	};
	
}
