#pragma once
#include <core/layer.h>
#include <core/window.h>
#include <core/application.h>
#include <scene/camera.h>

#include <graphics/sprite_batch.h>
#include <graphics/shader.h>

class EditorLayer : public Layer 
{
public:

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(float deltaTime) override;

	virtual void onEvent(const Event& e) override;
private:
	SpriteBatch *sprite_batch;
	Shader sprite_shader;
	Camera2D camera;
};