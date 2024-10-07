#pragma once
#include <math/vector2.h>
#include <core/camera.h>
#include <renderer/color.h>
#include <renderer/shaderprogram.h>

namespace ENGINE::RENDERER
{

	class LineRenderer
	{
	public:
		LineRenderer();
		~LineRenderer();

		void Begin(const CORE::Camera2D& camera);
		void Draw(const MATH::vector2& begin, const MATH::vector2& end, const RENDERER::Color& color);
		void End();

	private:
		unsigned int VAO, VBO;
		ShaderProgram *m_Program;
	};

}