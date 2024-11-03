#pragma once
#include <cstdint>
#include <math/vec2.h>
#include <math/vec4.h>
#include "sprite.h"

class SpriteBatch
{

public:
	SpriteBatch(uint32_t size);
	~SpriteBatch();

	void beginBatch();
	bool addSprite(const Sprite& sprite);
	void endBatch();

	void drawBatch();
private:
	bool m_BatchOpen = false;
	unsigned int m_StackTop = 0;

	unsigned int VAO, VBO, EBO;
	float *m_VertexArray; 

	uint32_t BATCH_SIZE;

};	