#include "sandboxapp.h"
#include <core/scene.h>
#include <core/input.h>
#include <renderer/texture.h>

#include <renderer/render.h>

using namespace ENGINE;

namespace APP
{

	CORE::Scene* scene;
	CORE::Camera camera;

	float t = 0.0f;
	float deltatime = 0.0f;

	void SandboxApp::Init()
	{
		RENDERER::Init();

		camera.Scale = 0.25f;

		scene = new CORE::Scene;
	    auto e = scene->CreateEntity();

		e->Texture = RENDERER::LoadTexture("res/_Run.png");
		e->Size = {e->Texture.Width/10.0f, (float)e->Texture.Height};
		e->UV1.x = 1/10.0f;
		e->Position.x = -60.0f;

		auto a = scene->CreateEntity();

		a->Texture = RENDERER::LoadTexture("res/_Idle.png");
		a->Size = {a->Texture.Width/10.0f, (float)a->Texture.Height};
		a->UV1.x = 1/10.0f;
		a->Position.x = 60.0f;

		scene->Init();

	}

	void SandboxApp::Update(f32 dt)
	{
		deltatime = dt;
		t += dt;

		if(t > 1/12.0f)
		{
			auto e = scene->GetEntityWithIndex(0);
			e->UV0.x += 1/10.0f;
			e->UV1.x += 1/10.0f;

			auto a = scene->GetEntityWithIndex(1);
			a->UV0.x += 1/10.0f;
			a->UV1.x += 1/10.0f;

			t = 0.0f;
		}

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
					else if(e.keyData.key == KEY_F)
					{
						std::cout << int(1/deltatime) << '\n'; 
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
