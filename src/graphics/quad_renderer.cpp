#include "quad_renderer.h"
#include <glad/glad.h>

QuadRenderer::QuadRenderer(uint16_t w, uint16_t h)
	: m_Viewport({w, h})
{}


QuadRenderer::QuadRenderer()
	: QuadRenderer(1280, 720)
{}

QuadRenderer::~QuadRenderer()
{}

void QuadRenderer::init()
{
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

void QuadRenderer::begin(Shader& program)
{	
	m_Program = &program;
	use_shader_program(program);
	shader_upload_vec2(program, "uViewport", float(m_Viewport.width), float(m_Viewport.height));


	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
}

void QuadRenderer::end()
{
	m_Program = nullptr;
	use_shader_program(Shader{0});

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void QuadRenderer::draw(int x, int y, int width, int height, const Color& color)
{
	if(m_Program == nullptr)
	{
		//TODO: log
		return;
	}

	shader_upload_vec2(*m_Program, "uPosition", float(x), float(y));
	shader_upload_vec2(*m_Program, "uSize", float(width), float(height));


	float r = color.r/255.0f;
	float g = color.g/255.0f;
	float b = color.b/255.0f;
	float a = color.a/255.0f;
	
	shader_upload_vec4(*m_Program, "uColor", r, g, b, a);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void QuadRenderer::draw(int x, int y, int width, int height) {
	this->draw(x, y, width, height, {0xff, 0xff, 0xff, 0xff});
}

void QuadRenderer::resizeViewport(uint16_t x, uint16_t y)
{
	m_Viewport.width = x;
	m_Viewport.height = y;
}

void QuadRenderer::cleanup()
{
	m_Program = nullptr;

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}