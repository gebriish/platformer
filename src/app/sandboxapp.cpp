#include "sandboxapp.h"
#include <core/scene.h>
#include <core/input.h>

#include <renderer/render.h>

using namespace ENGINE;

namespace APP
{

	CORE::Scene* scene;
	CORE::Camera camera;


	void SandboxApp::Init()
	{
		scene = new CORE::Scene;
		auto e = scene->CreateEntity();

		e->Size = {32};
		e->Color = {0xa5, 0x4a, 0x34, 0xff};

		scene->Init();

		RENDERER::Init();
	}

	void SandboxApp::Update(f32 dt)
	{
		MATH::vec2 vel(0.0f, 0.0f);
		if(INPUT::IsKeyPressed(KEY_W))
			vel.y = 1.0f;
		if(INPUT::IsKeyPressed(KEY_S))
			vel.y =-1.0f;
		if(INPUT::IsKeyPressed(KEY_D))
			vel.x = 1.0f;
		if(INPUT::IsKeyPressed(KEY_A))
			vel.x =-1.0f;
		
		vel = MATH::normalize(vel);
		camera.Position += vel * dt * 500;

		if(INPUT::IsKeyPressed(KEY_E))
			camera.Scale -= dt;
		if(INPUT::IsKeyPressed(KEY_Q))
			camera.Scale += dt;
		
		camera.Scale = std::max(camera.Scale, 0.0f);
	
		scene->Update(dt);
	
		RENDERER::RenderScene(*scene, camera);
	}
	


	void SandboxApp::OnEvent(ENGINE::CORE::Event& e)
	{
		using namespace ENGINE::CORE;

		switch (e.type)
		{

			case EventType::KEY : {
				if(e.keyData.action == PRESS)
				{
					if(e.keyData.key == KEY_TAB)
					{
						int polygon_mode;
						glGetIntegerv(GL_POLYGON_MODE, &polygon_mode);	
						glPolygonMode(GL_FRONT_AND_BACK, polygon_mode == GL_FILL ? GL_LINE : GL_FILL);
					}
				}


				break;
			}

			case EventType::CURSOR_MOVE : {
				if(INPUT::IsKeyPressed(KEY_SPACE))
				{
					scene->GetEntityWithIndex(0)->Position.x += e.cursorMoveData.Dx * camera.Scale;
					scene->GetEntityWithIndex(0)->Position.y -= e.cursorMoveData.Dy * camera.Scale;
				}
				break;
			}

			case EventType::RESIZE : {
				camera.Resize(e.resizeData.width, e.resizeData.height);
				glViewport(0, 0, camera.GetResolution(false).x, camera.GetResolution(false).y);
				break;
			}
		}
	}


	void SandboxApp::Cleanup()
	{
		delete scene;
		
		RENDERER::Cleanup();
	}

}
