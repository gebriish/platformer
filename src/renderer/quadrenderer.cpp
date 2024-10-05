#include "quadrenderer.h"


namespace ENGINE::RENDERER
{

	QuadRenderer::QuadRenderer()
	{
		this->init();
	}

	QuadRenderer::~QuadRenderer()
	{
		glDeleteVertexArrays(1, &m_QuadMesh.VAO);
    	glDeleteBuffers     (1, &m_QuadMesh.VBO);
    	glDeleteBuffers     (1, &m_QuadMesh.EBO);
	}

	void QuadRenderer::Draw
	(
		const MATH::vector2& position,
		const MATH::vector2& size,
		const RENDERER::TextureRegion& texture_region,
		const GLuint program
	)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_region.texture.ID);

		glUniform2f(glGetUniformLocation(program, "uPosition"), position.x, position.y);
		glUniform2f(glGetUniformLocation(program, "uSize"), size.x, size.y);
		glUniform2f(glGetUniformLocation(program, "uUVMin"), texture_region.uvMin.x, texture_region.uvMin.y);
		glUniform2f(glGetUniformLocation(program, "uUVMax"), texture_region.uvMax.x, texture_region.uvMax.y);
		glUniform4f(glGetUniformLocation(program, "uColor"), texture_region.color.GetR(),texture_region.color.GetG(),texture_region.color.GetB(),texture_region.color.GetA());
		
		glBindVertexArray(m_QuadMesh.VAO);
		glEnableVertexAttribArray(0);
		
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void QuadRenderer::init()
	{
		float vertices[] = {
			-0.5f,-0.5f,
			 0.5f,-0.5f,
			 0.5f, 0.5f,
			-0.5f, 0.5f,
		};
		
		unsigned int indices[] = { 
			0, 1, 2,
			0, 2, 3,
		};

		glGenVertexArrays(1, &m_QuadMesh.VAO);
		glGenBuffers     (1, &m_QuadMesh.VBO);
		glGenBuffers     (1, &m_QuadMesh.EBO);
		
		glBindVertexArray(m_QuadMesh.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_QuadMesh.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadMesh.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0); 
		glBindVertexArray(0); 
	}
}