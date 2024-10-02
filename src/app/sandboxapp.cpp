#include "sandboxapp.h"
#include <core/scene.h>
#include <core/input.h>
#include <renderer/texture.h>
#include <renderer/render.h>
#include "sceneloader.h"

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

		camera.Scale = 0.25f;
		camera.ClearColor = {0x18};

		scene = new CORE::Scene;
		LoadScene("res/demo.scene", *scene);
		scene->Init();
	}


	void SandboxApp::Update(f32 dt)
	{
		deltatime = dt;
		t += dt;

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
		UnloadTextures();
		delete scene;
		
		RENDERER::Cleanup();
	}

}
