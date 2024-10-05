#include "sandboxapp.h"
#include <core/input.h>
#include <renderer/quadrenderer.h>

using namespace ENGINE;

namespace APP
{
	
	RENDERER::Texture texture, white;
	std::shared_ptr<CORE::Entity> e, a;
	bool grounded = false;

	void SandboxApp::Init()
	{

		texture = RENDERER::LoadTexture("res/Texture/white.png");
		white = RENDERER::LoadTexture("res/Texture/white.png");

		DemoScene.MainCamera.Scale = 1/2.0f;
		e = DemoScene.CreateEntity();
		e->Size = {16, 32};
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
			grounded = true;
			v = 0.0f;
		}

		if(grounded && INPUT::IsKeyPressed(KEY_SPACE)) {
			v = - 300;
			grounded = false;
		}

		if(INPUT::IsKeyPressed(KEY_D))
			e->Position.x += dt * 300.0f;
		if(INPUT::IsKeyPressed(KEY_A))
			e->Position.x -= dt * 300.0f;

		if(INPUT::IsKeyPressed(KEY_F))
			printf("fps: %ld\n", u64(1/dt));

		DemoScene.MainCamera.Position = MATH::lerp(DemoScene.MainCamera.Position, e->Position, 15 * dt);

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
			}

			}	// key press

			break;
		}	// case key

		case EventType::CURSOR_MOVE : {
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
