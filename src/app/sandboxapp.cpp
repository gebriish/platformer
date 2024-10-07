#include "sandboxapp.h"
#include <core/input.h>

#include <cmath>
#include <renderer/quadrenderer.h>
#include <renderer/linerenderer.h>

using namespace ENGINE;

namespace APP
{
	CORE::Camera2D main_camera;
	MATH::vector2 position (0.0f, 0.0f);

	RENDERER::LineRenderer *lr;
	RENDERER::QuadRenderer *qr;

	void SandboxApp::Init()
	{
		qr = new RENDERER::QuadRenderer;
		lr = new RENDERER::LineRenderer;
	}

	void SandboxApp::Update(f32 dt)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		if(INPUT::IsKeyPressed(KEY_F))
			printf("%ld\n", u64(1/dt));

		auto[x, y] = INPUT::GetCursorPosition();
		MATH::vector2 pos = main_camera.ScreenToWorldPosition(x, y);

		qr->Begin(main_camera);
		qr->Draw(pos, {32,-32});
		qr->End();

		lr->Begin(main_camera);

		for(int i=0; i<12; i++)
		{
			f32 theta = i * 2 * 3.1415 / 12;
			MATH::vector2 p ( (f32) cos(theta), (f32) sin(theta));
			lr->Draw({0, 0}, p *  128, RENDERER::Color(0, 255, 0));
		}

		lr->End();
	}

	void SandboxApp::Cleanup()
	{
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
		}
	}
}
