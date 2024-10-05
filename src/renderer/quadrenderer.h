#pragma once
#include <math/vector2.h>
#include <renderer/color.h>
#include <renderer/shaderprogram.h>
#include <renderer/texturespec.h>

namespace ENGINE::RENDERER
{

	class QuadRenderer
	{
	public:
		QuadRenderer();
		~QuadRenderer();
	
		void Draw
		(
			const MATH::vector2& position,
			const MATH::vector2& size,
			const RENDERER::TextureRegion& texture_region,
			const GLuint program
		);

	private:

		void init();
	
	private:

		struct {
			unsigned int VAO, VBO, EBO;
		} m_QuadMesh;
	
	};

}