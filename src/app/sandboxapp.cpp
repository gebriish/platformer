#include "sandboxapp.h"
#include <core/input.h>

#include <renderer/quadrenderer.h>

using namespace ENGINE;

namespace APP
{
	CORE::Camera2D main_camera;

	MATH::vector2 position (0.0f, 0.0f);

	void SandboxApp::Init()
	{
	}

	void SandboxApp::Update(f32 dt)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		if(INPUT::IsKeyPressed(KEY_D))
			position += MATH::vector2(300, 0) * dt;
		if(INPUT::IsKeyPressed(KEY_A))
			position -= MATH::vector2(300, 0) * dt;
		if(INPUT::IsKeyPressed(KEY_W))
			position += MATH::vector2(0, 300) * dt;
		if(INPUT::IsKeyPressed(KEY_S))
			position -= MATH::vector2(0, 300) * dt;

		main_camera.Position = MATH::lerp(main_camera.Position, position, 13 * dt);
	}

	void SandboxApp::Cleanup()
	{
	}

	void SandboxApp::OnEvent(ENGINE::CORE::Event& e)
	{
		using namespace ENGINE::CORE;
		switch (e.type)
		{
			case EventType::RESIZE : {
				main_camera.Width = e.resizeData.width;
				main_camera.Height = e.resizeData.height;
				glViewport(0, 0, main_camera.Width, main_camera.Height);
				break;
			}
		}
	}
}
