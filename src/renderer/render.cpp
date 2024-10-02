#include "render.h"


#include <glad/glad.h>

namespace ENGINE::RENDERER
{
	ShaderProgram* SpriteShader;

	void Init()
	{
		SpriteShader = ShaderProgram::FromGLSLTextFiles("res/sprite.vert", "res/sprite.frag");
		glUniform1i(glGetUniformLocation(SpriteShader->GetRendererID(), "uSprite"), 0);


		glGenVertexArrays(1, &EntityQuad.VAO);
		glGenBuffers     (1, &EntityQuad.VBO);
		glGenBuffers     (1, &EntityQuad.EBO);

		float vertices[] = {
        	-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f,
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

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

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
		glClearColor(camera.ClearColor.GetR(), camera.ClearColor.GetG(), camera.ClearColor.GetB(), camera.ClearColor.GetA());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(SpriteShader->GetRendererID());
		glUniform2f(glGetUniformLocation(SpriteShader->GetRendererID(), "uResolution"), camera.GetResolution(true).x, camera.GetResolution(true).y);
		glUniform2f(glGetUniformLocation(SpriteShader->GetRendererID(), "uCamera"), camera.Position.x, camera.Position.y);

		glBindVertexArray(EntityQuad.VAO);
		glEnableVertexAttribArray(0);

		for(u64 i=0; i < scene.GetSize(); i++)
		{
			auto e = scene.GetEntityWithIndex(i);
			
			if(!e->Visible)
				continue;
			
			if(e->Texture.ID)
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, e->Texture.ID);
				}
			else
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, 0);
				}

			glUniform2f(glGetUniformLocation(SpriteShader->GetRendererID(), "uPosition"), e->Position.x, e->Position.y);
			glUniform2f(glGetUniformLocation(SpriteShader->GetRendererID(), "uOffset"), e->Center.x, e->Center.y);
			glUniform2f(glGetUniformLocation(SpriteShader->GetRendererID(), "uSize"), e->Size.x, e->Size.y);
			glUniform4f(glGetUniformLocation(SpriteShader->GetRendererID(), "uColor"), e->Color.GetR(), e->Color.GetG(), e->Color.GetB(), e->Color.GetA());

			glUniform2f(glGetUniformLocation(SpriteShader->GetRendererID(), "uUV0"), e->UV0.x, e->UV0.y);
			glUniform2f(glGetUniformLocation(SpriteShader->GetRendererID(), "uUV1"), e->UV1.x, e->UV1.y);


			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	
		}
	}
}