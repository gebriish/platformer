#include "batchrenderer.h"
#include <glad/glad.h>

namespace ENGINE::RENDERER
{
	EntityBatchRenderer::EntityBatchRenderer()
	{
		init();
	}

	EntityBatchRenderer::~EntityBatchRenderer()
	{
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteVertexArrays(1, &VAO);
	}


	void EntityBatchRenderer::Update()
	{
		
	}

	void EntityBatchRenderer::Draw()
	{

	}

	void EntityBatchRenderer::init()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, EntityBatchRenderer::SIZE * EntityVertex::SIZE * 4, nullptr, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, EntityVertex::SIZE, (void*) 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, EntityVertex::SIZE, (void*)(2 * sizeof(f32)));
		glEnableVertexAttribArray(1);
	
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, EntityVertex::SIZE, (void*)(6 * sizeof(f32)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, EntityVertex::SIZE, (void*)(8 * sizeof(f32)));
		glEnableVertexAttribArray(3);

		unsigned int indices[SIZE * 6];
		generateIndices(indices, SIZE);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void EntityBatchRenderer::generateIndices
		(unsigned int* indices, u16 size)
	{
		for(int i=0; i<size; i++)
		{
			indices[i * 6 + 0] = i * 4 + 0;
			indices[i * 6 + 1] = i * 4 + 1;
			indices[i * 6 + 2] = i * 4 + 2;

			indices[i * 6 + 3] = i * 4 + 0;
			indices[i * 6 + 4] = i * 4 + 2;
			indices[i * 6 + 5] = i * 4 + 3;
		}
	}
}