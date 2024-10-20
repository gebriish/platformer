#include "game_layer.h"
#include <core/application.h>
#include <core/input.h>

#include <iostream>

float dt;

GameLayer::GameLayer()
{
}

GameLayer::~GameLayer()
{
}

void GameLayer::onAttach()
{
	checker = load_texture("res/checker.png", TextureFiltering::NEAREST);

	m_QuadRenderer.resizeViewport(Application::Get().window().width, Application::Get().window().height);

	m_QuadRenderer.init("res/quad.vert", "res/quad.frag");

	use_shader_program(m_QuadRenderer.getProgram());
	shader_upload_int(m_QuadRenderer.getProgram(), "uSprite", 0);
}

void GameLayer::onDetach()
{
	delete_texture(checker);
	m_QuadRenderer.cleanup();
}

void GameLayer::onUpdate(float deltaTime)
{
	dt = deltaTime;
	auto[x, y] = Input::getCursorPosition();

	m_QuadRenderer.begin();
	bind_texture(checker, 0);

	m_QuadRenderer.draw(x, y, 64, 64);
}

void GameLayer::onEvent(const Event& e)
{
switch (e.type)
{
	case EventType::KEY_CLICK: {
		switch (e.keyData.key)
		{
			case KEY_F: {
				if(e.keyData.action == ActionCode::PRESS)
				{
					std::cout << "fps: " << int(1/dt) << '\n';
				}
				break;
			}
		}
		break;
	}
}
}