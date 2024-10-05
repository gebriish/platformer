#include "sandboxapp.h"
#include <core/input.h>
#include <renderer/quadrenderer.h>

using namespace ENGINE;

namespace APP
{
	
	RENDERER::Texture texture, white;
	std::shared_ptr<CORE::Entity> e, a;

	void SandboxApp::Init()
	{

		texture = RENDERER::LoadTexture("res/Texture/white.png");
		white = RENDERER::LoadTexture("res/Texture/white.png");

		DemoScene.MainCamera.Scale = 1/2.0f;
		e = DemoScene.CreateEntity();
		e->Size = {16, 32};
		e->Position = {0, 128};
		e->TextureRegion.texture = texture;


		a = DemoScene.CreateEntity();
		a->Size = {400, 16};
		a->Position = {0, - 100 - a->Size.y/2.0f};
		a->TextureRegion.texture = white;
		a->TextureRegion.color = {117, 204, 63, 255};
	}

	f32 v = 0;

	void SandboxApp::Update(f32 dt)
	{
        glClear(GL_COLOR_BUFFER_BIT);

		v += dt * 1000.0f;
		e->Position.y -= v * dt;

		if(e->Position.y <= -100 + e->Size.y/2.0)
		{
			e->Position.y = -100 + e->Size.y/2.0;
			v = 0.0f;
		}

		if(INPUT::IsKeyPressed(KEY_D))
			e->Position.x += dt * 300.0f;
		if(INPUT::IsKeyPressed(KEY_A))
			e->Position.x -= dt * 300.0f;

		DemoScene.Update(dt);
		
	}

	void SandboxApp::Cleanup()
	{
		RENDERER::DeleteTexture(texture);
	}

	void SandboxApp::OnEvent(ENGINE::CORE::Event& e)
	{
		using namespace ENGINE::CORE;

		switch (e.type)
		{
		case EventType::KEY : {
			if(e.keyData.action == PRESS)
			{

			switch (e.keyData.key)
			{	
				case KEY_SPACE : 
					v = - 300;
				break;
			}

			}	// key press

			break;
		}	// case key

		case EventType::CURSOR_MOVE : {

			if(INPUT::IsMouseButtonPressed(1))
			{
				DemoScene.MainCamera.Position
				= MATH::sub(DemoScene.MainCamera.Position, MATH::scale({(f32)e.cursorMoveData.Dx, -(f32)e.cursorMoveData.Dy}, DemoScene.MainCamera.Scale));
			}
			break;
		} // cursor move 


		case EventType::RESIZE : {
			glViewport(0, 0, e.resizeData.width, e.resizeData.height);
			DemoScene.MainCamera.Width  = e.resizeData.width;
			DemoScene.MainCamera.Height = e.resizeData.height;
			break;
		}
		}
	}
}
