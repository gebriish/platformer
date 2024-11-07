#include "line_batch2d.h"

#include <glad/glad.h>

LineBatch2d::LineBatch2d(uint32_t size)
{
	BATCH_SIZE = size;

	m_VertexArray = new float[BATCH_SIZE * 2 * sizeof(Line2dVertex)/sizeof(float)];

	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, BATCH_SIZE * 2 * sizeof(Line2dVertex), nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Line2dVertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Line2dVertex), (void*)offsetof(Line2dVertex, color));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

LineBatch2d::~LineBatch2d()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete[] m_VertexArray;
}

void LineBatch2d::beginBatch()
{
	m_BatchOpen = true;
	m_StackTop = 0;
}

bool LineBatch2d::addLine(const Line2d& line)
{
	if(m_StackTop >= BATCH_SIZE || !m_BatchOpen)
		return false;

	unsigned int vertex_size = sizeof(Line2dVertex)/sizeof(float);
	unsigned int array_top = m_StackTop * 2 * vertex_size;

	m_VertexArray[array_top + 0] = line.begin.x;
	m_VertexArray[array_top + 1] = line.begin.y;

	m_VertexArray[array_top + 2] = line.color.r/255.0f;
	m_VertexArray[array_top + 3] = line.color.g/255.0f;
	m_VertexArray[array_top + 4] = line.color.b/255.0f;
	m_VertexArray[array_top + 5] = line.color.a/255.0f;

	m_VertexArray[array_top + 6] = line.end.x;
	m_VertexArray[array_top + 7] = line.end.y;

	m_VertexArray[array_top + 8] = line.color.r/255.0f;
	m_VertexArray[array_top + 9] = line.color.g/255.0f;
	m_VertexArray[array_top +10] = line.color.b/255.0f;
	m_VertexArray[array_top +11] = line.color.a/255.0f;

	m_StackTop++;
	return true;
}

void LineBatch2d::endBatch()
{
	m_BatchOpen = false;
}

void LineBatch2d::drawBatch()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_StackTop * 2 * sizeof(Line2dVertex), m_VertexArray);

	for(int i=0; i<2; i++)
		glEnableVertexAttribArray(i);

	glDrawArrays(GL_LINES, 0, 2 * m_StackTop);
	
	for(int i=0; i<2; i++)
		glDisableVertexAttribArray(i);

	glBindVertexArray(0);
}