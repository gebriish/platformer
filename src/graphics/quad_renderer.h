#pragma once
#include <cstdint>
#include "shader.h"
#include "color.h"

class QuadRenderer
{
public:
	QuadRenderer();
	QuadRenderer(uint16_t w, uint16_t h);
	~QuadRenderer();

	void init();
	void begin(Shader& program);

	void draw(int x, int y, int width, int height, const Color& color);
	void draw(int x, int y, int width, int height);
	
	void end();

	void resizeViewport(uint16_t x, uint16_t y);

	void cleanup();	

private:
	unsigned int VAO, VBO, EBO;
	Shader* m_Program = nullptr;

	struct 
	{
		uint16_t width;
		uint16_t height;
	} m_Viewport;
};