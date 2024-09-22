#pragma once

#include "window.h"
#include <core/event.h>


namespace ENGINE::CORE
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

	protected:
		virtual void Init() = 0;
		virtual void Update(f32 dt) = 0;
		virtual void Cleanup() = 0;

		virtual void OnEvent(Event& e) = 0;
		
	protected:
		Window MainWindow{800, 500, "Platformer"};
	};
}
