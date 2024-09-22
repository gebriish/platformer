#include "renderer.h"
#include <world/entity.h>

#include "shaderprogram.h"

#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ENGINE::RENDERER 
{

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
	

		 float vertices[] = {
			 0.5f,  0.5f,  // top right
			 0.5f, -0.5f,  // bottom right
			-0.5f, -0.5f,  // bottom left
			-0.5f,  0.5f,  // top left 
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

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
	}

	void QueueEntityRenderCall(ENGINE::WORLD::Entity& entity)
	{
		EntityRenderQueue.push_back(EntityRenderCall{&entity});
	}

	void Render(f32 ar)
	{
		GLuint shaderid = SpriteShader->GetRendererID();
		glUseProgram(shaderid);
		glUniform1f(glGetUniformLocation(shaderid, "uAspectRatio"), ar);


		for(const auto& call : EntityRenderQueue)
		{
			WORLD::Entity* e = call.entity;
		
			glUniform2f(glGetUniformLocation(shaderid, "uOffset"), e->GetPosition().x, e->GetPosition().y);
			glUniform2f(glGetUniformLocation(shaderid, "uSize"), e->GetSize().x, e->GetSize().y);
			glUniform1f(glGetUniformLocation(shaderid, "uRotation"), e->GetRotation());
			glUniform4f(glGetUniformLocation(shaderid, "uColor"), e->GetColor().r, e->GetColor().g, e->GetColor().b, e->GetColor().a);

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

	}
}