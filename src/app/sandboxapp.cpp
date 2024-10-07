#include "sandboxapp.h"
#include <core/input.h>

#include <cmath>
#include <renderer/quadrenderer.h>
#include <renderer/linerenderer.h>

using namespace ENGINE;

namespace APP
{
	CORE::Camera2D main_camera;

	RENDERER::Texture idle, run;

	RENDERER::TextureRegion region;
	RENDERER::TextureRegion region2;

	RENDERER::QuadRenderer *qr;
	RENDERER::LineRenderer *lr;

	MATH::vector2 player_velocity(0.0f, 0.0f);
	MATH::vector2 player_position(0.0f, 128.0f);

	void SandboxApp::Init()
	{
		main_camera.Position = {64, 64};
		main_camera.Scale = 1/3.0f;
		
		idle = RENDERER::load_texture("res/Texture/_Idle.png");
		run = RENDERER::load_texture("res/Texture/_Run.png");

		region.texture = idle;
		region.uvMax.x = 1/10.0f; 
		
		
		region2.texture = RENDERER::load_texture("res/Texture/checker.png");
		region2.color = RENDERER::Color(128);

		lr = new RENDERER::LineRenderer;
		qr = new RENDERER::QuadRenderer;
	}

	bool running = false;
	bool grounded = false;
	float t = 0.0f;

	void SandboxApp::Update(f32 dt)
	{
		t += dt;
		glClear(GL_COLOR_BUFFER_BIT);

		if(INPUT::IsKeyPressed(KEY_E))
			main_camera.Scale -= dt;
		if(INPUT::IsKeyPressed(KEY_Q))
			main_camera.Scale += dt;
		if(INPUT::IsKeyPressed(KEY_F))
			printf("%ld\n", u64(1/dt));

		player_velocity.y -= 600 * dt;
		player_position += player_velocity * dt;
		if(player_position.y < 0.0f) {
			player_velocity.y = 0.0f;
			player_position.y = 0.0f;
			grounded = true;
		}


		if(running && region.texture.ID == idle.ID)
			region.texture = run;
		else if(!running && region.texture.ID == run.ID)
			region.texture = idle;

		if(t >= 1/16.0f)
			{
				region.uvMin += MATH::vector2(1/10.0f, 0.0);
				region.uvMax += MATH::vector2(1/10.0f, 0.0);
				t = 0.0f;
			}

		qr->Begin(main_camera);
		qr->Draw({0, 0}, {256, 256}, region2);
		qr->Draw(player_position, {120, 80 }, region);
		qr->End();

		lr->Begin(main_camera);
		lr->Draw({0.0f, 0.0f}, {800, 0.0f}, RENDERER::Color(255, 0, 0));
		lr->Draw({0.0f, 0.0f}, {0.0f, 800}, RENDERER::Color(0, 255, 0));
		lr->End();
	}

	void SandboxApp::Cleanup()
	{
		RENDERER::delete_texture(region.texture);
		RENDERER::delete_texture(region2.texture);

		delete lr;
		delete qr;
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

			case EventType::CURSOR_MOVE : {
				if(INPUT::IsKeyPressed(KEY_SPACE))
					main_camera.Position -= MATH::vector2{(f32) e.cursorMoveData.Dx, -(f32)e.cursorMoveData.Dy} * main_camera.Scale;
				break;
			}


			case EventType::KEY : {

				switch (e.keyData.key)
				{
					case KEY_RIGHT: {
						if(e.keyData.action == PRESS) {
							player_velocity.x = 160.0f;
							running = true;
							region.xFlip = false;
						}
						else if(e.keyData.action == RELEASE)
						{
							if(INPUT::IsKeyPressed(KEY_LEFT))
								{
									player_velocity.x =-160.0f;
									region.xFlip = true;
								}
							else 
								{
									player_velocity.x = 0.0f;
									running = false;
								}
						}
						break;
					}
					case KEY_LEFT: {
						if(e.keyData.action == PRESS) {
							running = true;
							player_velocity.x = -160.0f;
							region.xFlip = true;
						}
						else if(e.keyData.action == RELEASE)
						{
							if(INPUT::IsKeyPressed(KEY_RIGHT))
								{
									player_velocity.x = 160.0f;
									region.xFlip = false;
								}
							else 
								{
									player_velocity.x = 0.0f;
									running = false;
								}
						}
						break;
					}
					case KEY_SPACE : {
						if(e.keyData.action == PRESS && grounded)
						{
							player_velocity.y = 200.0f;	
							grounded = false;
						}	
						break;
					}
				}

				break;
			}
		}
	}
}
