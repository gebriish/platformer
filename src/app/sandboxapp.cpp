#include "sandboxapp.h"

#include <world/entity.h>
#include <renderer/renderer.h>

#include <core/input.h>

#include <glad/glad.h>

using namespace ENGINE;

namespace APP
{
	WORLD::Entity e0(0);
	WORLD::Entity e1(1);

	f32 AspectRatio = 1.6f;

	f32 deltaTime = 0.0f;

	void SandboxApp::Init()
	{	
		e0.SetPosition(-0.5f, 0.0f);
		e1.SetPosition(0.5f, 0.0f);

		e0.SetSize(1.3, 1.3);

		e0.SetRotation(-12.0f);
		e1.SetRotation(45.0f);

		e0.SetColor(RENDERER::Color(204, 57, 47, 255));

		RENDERER::Init();

		RENDERER::FlushEntityRenderQueue();
		RENDERER::QueueEntityRenderCall(e1);
		RENDERER::QueueEntityRenderCall(e0);
	}

	void SandboxApp::Update(f32 dt)
	{
		deltaTime = dt;

		if(INPUT::IsKeyPressed(KEY_D))
			printf("%i\n", (int)(1/dt));

		if(INPUT::IsKeyPressed(KEY_R))
			e0.AddRotation(dt * 90.0f);
		
		RENDERER::Prepair();
		RENDERER::Render(AspectRatio);
	}

	void SandboxApp::OnEvent(ENGINE::CORE::Event& e)
	{
		using namespace ENGINE::CORE;

		switch (e.type)
		{
			case EventType::RESIZE : {
				AspectRatio = (f32) e.resizeData.width/e.resizeData.height;
				glViewport(0, 0, e.resizeData.width, e.resizeData.height);
				break;
			}

			case EventType::CURSOR_MOVE: {
				if(INPUT::IsKeyPressed(KEY_SPACE)) {
					f32 dx = e.cursorMoveData.Dx / Window::Get().GetWidth();
					f32 dy = -e.cursorMoveData.Dy / Window::Get().GetHeight();
					e1.AddPosition(dx * 2 * AspectRatio, dy * 2);
				}
				break;
			}
		}

	}


	void SandboxApp::Cleanup()
	{
		RENDERER::Cleanup();
	}

}
