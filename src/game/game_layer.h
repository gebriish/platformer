#pragma once
#include "../core/layer.h"

class GameLayer : public Layer 
{
public:

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(float deltaTime) override;

	virtual void onEvent(const Event& e) override;
};