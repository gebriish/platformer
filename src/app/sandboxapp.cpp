#include "sandboxapp.h"

#include <glad/glad.h>
#include <graphics/shaderprogram.h>

#include <iostream>


namespace APP
{
	f32 deltaTime = 0.0f;
	f32 aspectRatio = 1.6f;
	ENGINE::GRAPHICS::ShaderProgram* program;
	u32 VAO, VBO, EBO;

	void SandboxApp::Init()
	{
		float vertices[] = {
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0); 
		glBindVertexArray(0); 


		program = ENGINE::GRAPHICS::ShaderProgram::FromGLSLTextFiles("res/sprite.vert", "res/sprite.frag");
	

		glUseProgram(program->GetRendererID());
		glUniform1f(glGetUniformLocation(program->GetRendererID(), "uAspectRatio"), aspectRatio);

	}



	void SandboxApp::Update(f32 dt)
	{
		deltaTime = dt;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program->GetRendererID());
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	}


	void SandboxApp::OnEvent(ENGINE::CORE::Event& e)
	{
		using namespace ENGINE::CORE;

		switch(e.type)
		{
			case EventType::RESIZE : {
				glViewport(0, 0, e.resizeData.width, e.resizeData.height);

				aspectRatio = (f32)e.resizeData.width / e.resizeData.height;

				glUseProgram(program->GetRendererID());
				glUniform1f(glGetUniformLocation(program->GetRendererID(), "uAspectRatio"), aspectRatio);

				break;
			}

			case EventType::KEY : {

				if(e.keyData.action == PRESS) {
					switch (e.keyData.key) {
						case KEY_F: {
							std::cout << int(1/deltaTime) << std::endl;
							break;
						}

						case KEY_TAB: {
							int polygonMode;
							glGetIntegerv(GL_POLYGON_MODE, &polygonMode);

							if (polygonMode == GL_FILL)
								polygonMode = GL_LINE;
							else 
								polygonMode = GL_FILL;

							glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
						}
					}

				}
				break;
			}

			case EventType::CURSOR_MOVE : {
				break;
			}
		}
	}


	void SandboxApp::Cleanup()
	{
		glDeleteVertexArrays(1, &VAO);
    	glDeleteBuffers(1, &VBO);
    	glDeleteBuffers(1, &EBO);

		delete program;
	}

}