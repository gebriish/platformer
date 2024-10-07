#pragma once
#include <core/camera.h>
#include <renderer/shaderprogram.h>
#include <renderer/texturespec.h>
#include <renderer/color.h>
#include <math/vector2.h>

namespace ENGINE::RENDERER
{

	class QuadRenderer
	{
	public:
		QuadRenderer();
		~QuadRenderer();

		void Begin(const CORE::Camera2D& camera);
		void Draw(const MATH::vector2& position, const MATH::vector2& size);
		void Draw(const MATH::vector2& position, const MATH::vector2& size, const Color& color);
		void Draw(const MATH::vector2& position, const MATH::vector2& size, const TextureRegion& region);
		void End();

	private:
		unsigned int VAO, VBO, EBO;
		ShaderProgram* m_Program;
		Texture m_WhiteTexture;

	};
	

	

}