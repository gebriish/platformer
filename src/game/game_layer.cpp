#include "game_layer.h"
#include "../core/window.h"
#include "../graphics/quad_renderer.h"
#include "../core/application.h"
#include "../core/input.h"

Shader sprite;
QuadRenderer qr;


void GameLayer::onAttach()
{
	load_glsl_shader("res/quad.vert", "res/quad.frag", sprite);

	qr.init();
	qr.resizeViewport(640, 480);
}

void GameLayer::onDetach()
{
	qr.cleanup();
}

int x, y, w = 32, h = 32;

void GameLayer::onUpdate(float deltaTime)
{
	auto& window = Application::Get().window();
	clear_viewport(color_from_hexcode("000000"));

	if(x < 0)
		x = 0;
	else if(x > Application::Get().window().width - 8)
		x = Application::Get().window().width - 8;
	if(y < 0)
		y = 0;
	else if(y > Application::Get().window().height - 8)
		y = Application::Get().window().height - 8;

	qr.begin(sprite);
	qr.draw(x, y, w, h);
	qr.end();
}

void GameLayer::onEvent(const Event& e)
{
	if(e.type == EventType::RESIZE)
	{
		auto& window = Application::Get().window();
		set_render_region(window, e.resizeData.width, e.resizeData.height);
		qr.resizeViewport(window.width, window.height);
	}
	else if(e.type == EventType::CURSOR_MOVE)
	{
		if(Input::isMouseButtonPressed(0))
		{
			x += e.cursorMoveData.Dx;
			y += e.cursorMoveData.Dy;
		}
		else if(Input::isMouseButtonPressed(1))
		{
			w += e.cursorMoveData.Dx;
			h += e.cursorMoveData.Dy;
		}
	}
}
