#pragma once
#include <core/scene.h>
#include <core/camera.h>
#include "shaderprogram.h"

namespace ENGINE::RENDERER
{

	struct {
		unsigned int VAO, VBO, EBO;
	} EntityQuad;

	void Init();
	void Cleanup();

	void RenderScene(CORE::Scene& scene, const CORE::Camera& camera);

}