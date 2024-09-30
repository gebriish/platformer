#include "render.h"


#include <glad/glad.h>

namespace ENGINE::RENDERER
{
	ShaderProgram* SpriteShader;

	void Init()
	{
		SpriteShader = ShaderProgram::FromGLSLTextFiles("res/sprite.vert", "res/sprite.frag");

		glGenVertexArrays(1, &EntityQuad.VAO);
		glGenBuffers     (1, &EntityQuad.VBO);
		glGenBuffers     (1, &EntityQuad.EBO);

		float vertices[] = {
        	-0.5f, -0.5f, 0,0,
			 0.5f, -0.5f, 1,0,
			 0.5f,  0.5f, 1,1,
			-0.5f,  0.5f, 0,1,
		};

		unsigned int indices[] = { 
			0, 1, 2,
			0, 2, 3,
		};

		glBindVertexArray(EntityQuad.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, EntityQuad.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EntityQuad.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0); 
		glBindVertexArray(0); 

	}

	void Cleanup()
	{
		glDeleteVertexArrays(1, &EntityQuad.VAO);
		glDeleteBuffers(1, &EntityQuad.VBO);
		glDeleteBuffers(1, &EntityQuad.EBO);
		glDeleteProgram(SpriteShader->GetRendererID());

		delete SpriteShader;

		SpriteShader = nullptr;
	}

	void RenderScene(CORE::Scene& scene, const CORE::Camera& camera)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(SpriteShader->GetRendererID());
		glUniform2f(glGetUniformLocation(SpriteShader->GetRendererID(), "uResolution"), camera.GetResolution(true).x, camera.GetResolution(true).y);
		glUniform2f(glGetUniformLocation(SpriteShader->GetRendererID(), "uCamera"), camera.Position.x, camera.Position.y);

		glBindVertexArray(EntityQuad.VAO);

		for(u64 i=0; i < scene.GetSize(); i++)
		{
			auto e = scene.GetEntityWithIndex(i);
			
			if(!e->Visible)
				continue;
			
			glUniform2f(glGetUniformLocation(SpriteShader->GetRendererID(), "uPosition"), e->Position.x, e->Position.y);
			glUniform2f(glGetUniformLocation(SpriteShader->GetRendererID(), "uOffset"), e->Center.x, e->Center.y);
			glUniform2f(glGetUniformLocation(SpriteShader->GetRendererID(), "uSize"), e->Size.x, e->Size.y);
			glUniform4f(glGetUniformLocation(SpriteShader->GetRendererID(), "uColor"), e->Color.GetR(), e->Color.GetG(), e->Color.GetB(), e->Color.GetA());

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	
		}
	}
}