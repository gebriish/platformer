#pragma once
#include "../core/layer.h"
#include "../graphics/quad_renderer.h"
#include "../graphics/texture.h"


class GameLayer : public Layer 
{
public:
	GameLayer();
	virtual ~GameLayer();

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(float deltaTime) override;

	virtual void onEvent(const Event& e) override;

private:
	Texture checker;
	QuadRenderer m_QuadRenderer;
};