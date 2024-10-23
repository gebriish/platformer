#pragma once
#include <cstdint>
#include "shader.h"
#include "color.h"

class LineRenderer
{
public:
	LineRenderer();
	LineRenderer(uint16_t w, uint16_t h);
	~LineRenderer();

	void init();
	void begin(Shader& program);

	void draw(int x1, int y1, int x2, int y2, const Color& color);
	void draw(int x1, int y1, int x2, int y2);

	void end();
	
	void resizeViewport(uint16_t x, uint16_t y);

	void cleanup();

private:
	unsigned int VAO, VBO, EBO;
	Shader* m_Program = nullptr;

	struct {
		uint16_t width;
		uint16_t height;
	}m_Viewport;
};