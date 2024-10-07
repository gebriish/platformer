#include "linerenderer.h"

namespace ENGINE::RENDERER
{

	LineRenderer::LineRenderer()
	{
		m_Program = ShaderProgram::FromGLSLTextFiles("res/line.vert", "res/line.frag");
	
		float vertices[] = {
			0, 0,
			1, 1,
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}
	
	LineRenderer::~LineRenderer()
	{
		glDeleteProgram(m_Program->GetRendererID());
		delete m_Program;

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void LineRenderer::Begin(const CORE::Camera2D& camera)
	{
		GLuint program_id = m_Program->GetRendererID();

		glUseProgram(program_id);

		glUniform2f(glGetUniformLocation(program_id, "uCamera.position"), camera.Position.x, camera.Position.y);
		glUniform2f(glGetUniformLocation(program_id, "uCamera.resolution"), camera.Width * camera.Scale, camera.Height * camera.Scale);
		

		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);
	} 

	void LineRenderer::Draw(const MATH::vector2& begin, const MATH::vector2& end, const RENDERER::Color& color)
	{
		GLuint program_id = m_Program->GetRendererID();

		glUniform4f(glGetUniformLocation(program_id, "uColor"), color.GetR(), color.GetG(), color.GetB(), color.GetA());
		glUniform2f(glGetUniformLocation(program_id, "uBegin"), begin.x, begin.y);
		glUniform2f(glGetUniformLocation(program_id, "uEnd"), end.x, end.y);

		glDrawArrays(GL_LINES, 0, 2);
	}

	void LineRenderer::End()
	{
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
		glUseProgram(0);
	}

}