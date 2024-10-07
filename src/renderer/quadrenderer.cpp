#include "quadrenderer.h"

namespace ENGINE::RENDERER
{
	QuadRenderer::QuadRenderer()
	{
		m_Program = ShaderProgram::FromGLSLTextFiles("res/quad.vert", "res/quad.frag");
		glUniform1i(glGetUniformLocation(m_Program->GetRendererID(), "uTexture"), 0);

		m_WhiteTexture = load_texture("res/Texture/white.png");

		float quadVertices[] = {
			0, 0,
			1, 0,
			1, 1,
			0, 1,
		};

		unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3 
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}


	QuadRenderer::~QuadRenderer()
	{
		delete_texture(m_WhiteTexture);

		glDeleteProgram(m_Program->GetRendererID());
		delete m_Program;

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void QuadRenderer::Begin(const CORE::Camera2D& camera)
	{
		GLuint program_id = m_Program->GetRendererID();

		glUseProgram(program_id);

		glUniform2f(glGetUniformLocation(program_id, "uCamera.position"), camera.Position.x, camera.Position.y);
		glUniform2f(glGetUniformLocation(program_id, "uCamera.resolution"), camera.Width * camera.Scale, camera.Height * camera.Scale);
		

		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);
	}

	void QuadRenderer::Draw(const MATH::vector2& position, const MATH::vector2& size, const TextureRegion& region)
	{
		bind_texture(region.texture, 0);
		GLuint program_id = m_Program->GetRendererID();

		glUniform2f(glGetUniformLocation(program_id, "uSprite.position"), position.x, position.y);
		glUniform2f(glGetUniformLocation(program_id, "uSprite.size"), size.x, size.y);

		glUniform4f(glGetUniformLocation(program_id, "uColor"), region.color.GetR(), region.color.GetG(), region.color.GetB(), region.color.GetA());

		glUniform2f(glGetUniformLocation(program_id, "uUVmin"), region.uvMin.x, region.uvMin.y);
		glUniform2f(glGetUniformLocation(program_id, "uUVmax"), region.uvMax.x, region.uvMax.y);


		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void QuadRenderer::Draw(const MATH::vector2& position, const MATH::vector2& size)
	{
		TextureRegion region;
		region.color   = Color(0xff);
		region.texture = m_WhiteTexture;

		this->Draw(position, size, region);
	}

	void QuadRenderer::Draw(const MATH::vector2& position, const MATH::vector2& size, const Color& color)
	{
		TextureRegion region;
		region.color   = color;
		region.texture = m_WhiteTexture;

		this->Draw(position, size, region);
	}

	void QuadRenderer::End()
	{
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}