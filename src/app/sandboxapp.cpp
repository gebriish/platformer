#include "sandboxapp.h"
#include <core/input.h>

#include <cmath>
#include <renderer/quadrenderer.h>
#include <renderer/linerenderer.h>

using namespace ENGINE;

namespace APP
{
	CORE::Camera2D main_camera;
	RENDERER::TextureRegion region;
	RENDERER::TextureRegion region2;

	RENDERER::QuadRenderer *qr;
	RENDERER::LineRenderer *lr;

	void SandboxApp::Init()
	{
		main_camera.Scale = 1/3.0f;
		region.texture = RENDERER::load_texture("res/Texture/tile.png");
		region2.texture = RENDERER::load_texture("res/Texture/checker.png");
		region2.color = RENDERER::Color(128);

		lr = new RENDERER::LineRenderer;
		qr = new RENDERER::QuadRenderer;
	}

	void SandboxApp::Update(f32 dt)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		if(INPUT::IsKeyPressed(KEY_E))
			main_camera.Scale -= dt;
		if(INPUT::IsKeyPressed(KEY_Q))
			main_camera.Scale += dt;

		if(INPUT::IsKeyPressed(KEY_F))
			printf("%ld\n", u64(1/dt));

		qr->Begin(main_camera);
		qr->Draw({0, 0}, {256, 256}, region2);
		qr->Draw({0, 0}, {128, 128}, region);
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
		}
	}
}
