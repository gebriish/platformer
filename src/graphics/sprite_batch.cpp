#include "sprite_batch.h"

#include <glad/glad.h>
#include <cmath>

SpriteBatch::SpriteBatch(uint32_t size)
	: BATCH_SIZE(size)
{
	
	m_VertexArray = new float[BATCH_SIZE * 4 * sizeof(SpriteVertex)/sizeof(float)];

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, BATCH_SIZE * 4 * sizeof(SpriteVertex), nullptr, GL_DYNAMIC_DRAW);

	unsigned int *indices = new unsigned int[BATCH_SIZE * 6];

	for(int i=0; i<BATCH_SIZE; i++)	
	{
		indices[i * 6 + 0] = i * 4 + 0;
		indices[i * 6 + 1] = i * 4 + 1;
		indices[i * 6 + 2] = i * 4 + 2;

		indices[i * 6 + 3] = i * 4 + 0;
		indices[i * 6 + 4] = i * 4 + 2;
		indices[i * 6 + 5] = i * 4 + 3;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * BATCH_SIZE * 6, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (void*)offsetof(SpriteVertex, color));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (void*)offsetof(SpriteVertex, texcoord));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	delete[] indices;
}

SpriteBatch::~SpriteBatch()
{	

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	delete[] m_VertexArray;
}

void SpriteBatch::beginBatch()
{
	m_BatchOpen = true;
	m_StackTop = 0;
}

bool SpriteBatch::addSprite(const Sprite& sprite)
{
	if(m_StackTop >= BATCH_SIZE || !m_BatchOpen)
	{
		return false;
	}

	vec2 pos(-0.5f);
	unsigned int vertex_size = sizeof(SpriteVertex)/sizeof(float);
	unsigned int array_top = m_StackTop * 4 * vertex_size;

	vec2 texture_coord_size_vec = sprite.texture_coord_max - sprite.texture_coord_min;

	for(int i=0; i<4; i++)
	{
		switch (i)
		{
			case 1:
				pos.x = 0.5f;
				break;
			case 2:
				pos.y = 0.5f;
				break;
			case 3:
				pos.x = -0.5f;
				break;
		}

		vec2 point = vec2(pos.x * sprite.size.x, pos.y * sprite.size.y) - sprite.offset;

		float c_val = (float) cos(sprite.rotation * M_PI / 180);
		float s_val = (float) sin(sprite.rotation * M_PI / 180);

		m_VertexArray[array_top + i * vertex_size + 0] = point.x * c_val - point.y * s_val + sprite.position.x;
		m_VertexArray[array_top + i * vertex_size + 1] = point.y * c_val + point.x * s_val + sprite.position.y;

		m_VertexArray[array_top + i * vertex_size + 2] = sprite.color.r/255.0;
		m_VertexArray[array_top + i * vertex_size + 3] = sprite.color.g/255.0;
		m_VertexArray[array_top + i * vertex_size + 4] = sprite.color.b/255.0;
		m_VertexArray[array_top + i * vertex_size + 5] = sprite.color.a/255.0;

		m_VertexArray[array_top + i * vertex_size + 6] = (pos.x + 0.5) * texture_coord_size_vec.x + sprite.texture_coord_min.x;
		m_VertexArray[array_top + i * vertex_size + 7] = (0.5 - pos.y) * texture_coord_size_vec.y + sprite.texture_coord_min.y;
	}

	m_StackTop++;
	return true;
}

void SpriteBatch::endBatch()
{
	m_BatchOpen = false;
}

void SpriteBatch::drawBatch()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_StackTop * 4 * sizeof(SpriteVertex), m_VertexArray);

	for(int i=0; i<3; i++)
		glEnableVertexAttribArray(i);

	glDrawElements(GL_TRIANGLES, m_StackTop * 6, GL_UNSIGNED_INT, nullptr);

	for(int i=0; i<3; i++)
		glDisableVertexAttribArray(i);

	glBindVertexArray(0);
}