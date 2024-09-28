#include "renderer.h"
#include <world/entity.h>

#include "shaderprogram.h"

#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>

namespace ENGINE::RENDERER 
{

	f32 vertices[512 * 8 * 4];		// 512 is batch size

	struct EntityRenderCall
	{
		ENGINE::WORLD::Entity* entity;
	};	

	ShaderProgram* SpriteShader;
	std::vector<EntityRenderCall> EntityRenderQueue;	

	unsigned int VAO, VBO, EBO;

	void Init()
	{
		SpriteShader = ShaderProgram::FromGLSLTextFiles("res/sprite.vert", "res/sprite.frag");

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), nullptr, GL_DYNAMIC_DRAW);

		unsigned int indices[512 * 6];
		for(int i=0; i<512; i++)
		{
			indices[i * 6 + 0] = i * 4 + 0;
			indices[i * 6 + 1] = i * 4 + 1;
			indices[i * 6 + 2] = i * 4 + 2;

			indices[i * 6 + 3] = i * 4 + 0;
			indices[i * 6 + 4] = i * 4 + 2;
			indices[i * 6 + 5] = i * 4 + 3;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void*)(2 * sizeof(f32)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void*)(6 * sizeof(f32)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0); 
		glBindVertexArray(0);

	}

	void Cleanup()
	{
		delete SpriteShader;
	}

	void FlushEntityRenderQueue()
	{
		EntityRenderQueue.clear();
	}

	void Prepair()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);	

		uint64_t entityIndex = 0;

		for(const auto& call : EntityRenderQueue)
		{
			WORLD::Entity* e = call.entity;
			if(e->UpdateFlag()) {
				float xAdd = -0.5f, yAdd = -0.5f;
				int vertexBase = entityIndex * 32; // 4 vertices * 8 attributes per vertex
				for(int i = 0; i < 4; i++)
				{
					int offset = i * 8; 
					switch (i)
					{
						case 1:
							xAdd = 0.5f;
							break;
						case 2:
							yAdd = 0.5f;
							break;
						case 3:
							xAdd = -0.5f;
					}

					float c = cos(e->GetRotation());
					float s = sin(e->GetRotation());

					float x = c * xAdd - s * yAdd;
					float y = s * xAdd + c * yAdd;

					vertices[vertexBase + offset + 0] = e->GetPosition().x + x * e->GetSize().x; // Position x
					vertices[vertexBase + offset + 1] = e->GetPosition().y + y * e->GetSize().y; // Position y
					
					// Assuming the next attributes are normals or repeated position (may need clarification)
					vertices[vertexBase + offset + 2] = e->GetColor().r/255.0f;
					vertices[vertexBase + offset + 3] = e->GetColor().g/255.0f;
					vertices[vertexBase + offset + 4] = e->GetColor().b/255.0f;
					vertices[vertexBase + offset + 5] = e->GetColor().a/255.0f;

					// Texture coordinates or other attributes
					vertices[vertexBase + offset + 6] = xAdd + 0.5f; // UV X
					vertices[vertexBase + offset + 7] = yAdd + 0.5f; // UV Y
				}
				e->SetUpdateFlag(false);
			}
			entityIndex++;
		}
	}

	void QueueEntityRenderCall(ENGINE::WORLD::Entity& entity)
	{
		EntityRenderQueue.push_back(EntityRenderCall{&entity});
	}

	void Render(u16 width, u16 height)
	{
		GLuint shaderid = SpriteShader->GetRendererID();
		glUseProgram(shaderid);
		glUniform2f(glGetUniformLocation(shaderid, "uResolution"), width, height);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);

		glDrawElements(GL_TRIANGLES, 6 * EntityRenderQueue.size(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);


        glBindVertexArray(0);
	}
}