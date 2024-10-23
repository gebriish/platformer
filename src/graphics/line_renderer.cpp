#include "line_renderer.h"

#include <glad/glad.h>

LineRenderer::LineRenderer(uint16_t w, uint16_t h)
	: m_Viewport({w, h})
{}

LineRenderer::LineRenderer()
	: LineRenderer(1280, 720)
{}

LineRenderer::~LineRenderer()
{}

void LineRenderer::init()
{
	float lineVertices[] = {
		 0.0,  0.0,
		-1.0, -1.0,
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void LineRenderer::begin(Shader& program)
{
	m_Program = &program;
	use_shader_program(program);

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
}

void LineRenderer::end()
{
	m_Program = nullptr;
	use_shader_program(Shader{0});

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void LineRenderer::draw(int x1, int y1, int x2, int y2, const Color& color)
{
	shader_upload_vec2(*m_Program, "uBegin", float(x1), float(y1));
	shader_upload_vec2(*m_Program, "uEnd", float(x2), float(y2));
	
	float r = color.r/255.0f;
	float g = color.g/255.0f;
	float b = color.b/255.0f;
	float a = color.a/255.0f;

	shader_upload_vec4(*m_Program, "uColor", r, g, b, a);
	
	glDrawArrays(GL_LINES, 0, 2);
}

void LineRenderer::draw(int x1, int y1, int x2, int y2)
{
	this->draw(x1, y1, x2, y2, Color{255,255,255,255});
}

void LineRenderer::resizeViewport(uint16_t x, uint16_t y)
{
	m_Viewport.width = x;
	m_Viewport.height = y;
}
void LineRenderer::cleanup()
{
	m_Program = nullptr;

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}