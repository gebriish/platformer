#pragma once

#include <core/layer.h>

#include "scenes/test_scene.h"

class MainLayer : public Layer
{
public:
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onEvent(const Event& e) override;

private:
	TestScene* test_scene;
};