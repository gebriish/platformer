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

	WORLD::Entity *grid[256];

	f32 AspectRatio = 1.6f;

	f32 deltaTime = 0.0f;

	void SandboxApp::Init()
	{	

		RENDERER::Init();

		RENDERER::FlushEntityRenderQueue();

		e0.SetPosition(-32, 0.0f);
		e1.SetPosition(32, 0.0f);

		e0.SetSize(64, 64);
		e1.SetSize(64, 64);
		
		e0.SetColor(RENDERER::Color(204, 57, 47, 255));

		for(int i=0; i<16; i++)
		{
			for(int j=0; j<16; j++)
			{
				WORLD::Entity *e = new WORLD::Entity(i * 16 + j + 2);
				e->SetSize(10, 10);
				e->SetPosition((i - 8) * 16 , (j - 8) * 16);
				
				RENDERER::Color c ((u8)((i / 15.0f) * 255), (u8)((j / 15.0f) * 255), 0, 255);
				e->SetColor(c);
				grid[i * 16 + j] = e;
				RENDERER::QueueEntityRenderCall(*e);
			}
		}

		RENDERER::QueueEntityRenderCall(e1);
		RENDERER::QueueEntityRenderCall(e0);

	}

	void SandboxApp::Update(f32 dt)
	{
		deltaTime = dt;

		if(INPUT::IsKeyPressed(KEY_D))
			printf("%i\n", (int)(1/dt));

		if(INPUT::IsKeyPressed(KEY_R))
			e0.AddRotation(dt * 2.0f);
		
		RENDERER::Prepair();
		RENDERER::Render(MainWindow.GetWidth(), MainWindow.GetHeight());
	}

	void SandboxApp::OnEvent(ENGINE::CORE::Event& e)
	{
		using namespace ENGINE::CORE;

		switch (e.type)
		{

			case EventType::KEY: {
				if(e.keyData.action == PRESS)
				{
					if(e.keyData.key == KEY_W)
					{
						int polygon_mode;
						glGetIntegerv(GL_POLYGON_MODE, &polygon_mode);
						glPolygonMode(GL_FRONT_AND_BACK, polygon_mode == GL_FILL ? GL_LINE : GL_FILL);
					}
				}

				break;
			}

			case EventType::RESIZE: {
				glViewport(0, 0, e.resizeData.width, e.resizeData.height);
				break;
			}

			case EventType::CURSOR_MOVE: {
				if(INPUT::IsKeyPressed(KEY_SPACE)) {
					f32 dx = e.cursorMoveData.Dx;
					f32 dy = -e.cursorMoveData.Dy;
					e1.AddPosition(dx, dy);
				}
				break;
			}
		}

	}


	void SandboxApp::Cleanup()
	{
		RENDERER::Cleanup();

		for(WORLD::Entity* e : grid)
			delete e;
	}

}
