#pragma once
#include <scene/scene2d.h>

class TestScene : public Scene2D
{
public:
	virtual void onLoad() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onUnload() override;
};