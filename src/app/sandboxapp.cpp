#include "sandboxapp.h"
#include <core/scene.h>
#include <core/input.h>
#include <renderer/texture.h>
#include <renderer/render.h>
#include "sceneloader.h"

#include <cmath>

using namespace ENGINE;

namespace APP
{

	CORE::Scene* scene;
	CORE::Camera camera;

	float t = 0.0f;
	float deltatime = 0.0f;

	MATH::vec2 pos{0.0f, 0.0f};

	void SandboxApp::Init()
	{
		RENDERER::Init();

		camera.Scale = 0.5f;
		camera.ClearColor = {0x18};

		scene = new CORE::Scene;
		LoadScene("res/demo.scene", *scene);

		auto e = scene->CreateEntity();
		e->Texture = scene->GetTexture(1);
		e->Size = {8};
		e->UV0 = {0.0f, 0.375f};
		e->UV1 = e->UV0 + MATH::vec2{1/16.0f, 1/16.0f};
		e->Position = {20, -12};
	}


	int sprite_index = 0;
	float x = 0;
	void SandboxApp::Update(f32 dt)
	{
		deltatime = dt;
		t += dt;
		x += dt;

		auto e = scene->GetEntityWithIndex(1);	


		if(t > 1/8.0f)
		{
			
			if(sprite_index < 9) {
				e->UV0.x += 1/16.0f;
				e->UV1.x += 1/16.0f;
			}			
			else{
				e->UV0 = {0.0f, 0.375f};
				e->UV1 = e->UV0 + MATH::vec2{1/16.0f, 1/16.0f};
				sprite_index = 0;
			}
			sprite_index++;
			t = 0.0f;
		}


		if(INPUT::IsKeyPressed(KEY_E))
			camera.Scale -= dt;	
		if(INPUT::IsKeyPressed(KEY_Q))
			camera.Scale += dt;

		camera.Scale = std::max(camera.Scale, 0.0f);

		if(INPUT::IsKeyPressed(KEY_D))
			pos.x += dt * 256;	
		if(INPUT::IsKeyPressed(KEY_A))
			pos.x -= dt * 256;
		if(INPUT::IsKeyPressed(KEY_W))
			pos.y += dt * 256;	
		if(INPUT::IsKeyPressed(KEY_S))
			pos.y -= dt * 256;

		camera.Position = MATH::lerp(camera.Position, pos, 10 * dt);	
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
					if(e.keyData.key == KEY_F)
					{
						std::cout << int(1/deltatime) << '\n'; 
					}
					else if(e.keyData.key == KEY_G)
					{
						scene->RemoveEntity(1);
					}
				}


				break;
			}

			case EventType::CURSOR_MOVE : {
				if(INPUT::IsKeyPressed(KEY_SPACE))
				{
					pos.x -= e.cursorMoveData.Dx * camera.Scale;
					pos.y += e.cursorMoveData.Dy * camera.Scale;
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
