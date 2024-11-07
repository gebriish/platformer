#pragma once
#include <cstdint>
#include <graphics/color.h>
#include <math/vec2.h>
#include <math/vec4.h>

struct Line2dVertex
{
	vec2 position;
	vec4 color;
};

struct Line2d
{
	vec2 begin;
	vec2 end;
	Color color;
};

class LineBatch2d
{
public:
	LineBatch2d(uint32_t size);
	~LineBatch2d();

	void beginBatch();
	bool addLine(const Line2d& line);
	void endBatch();

	void drawBatch();

private:
	bool m_BatchOpen = false;
	unsigned int m_StackTop = 0;

	unsigned VAO, VBO;
	float *m_VertexArray;

	uint32_t BATCH_SIZE;
};