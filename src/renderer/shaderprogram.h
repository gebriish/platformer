#pragma once

#include <string>
#include <glad/glad.h>

namespace ENGINE::RENDERER
{
	class ShaderProgram
	{
	public:
		~ShaderProgram();

		inline GLuint GetRendererID() const { return m_RendererID; }
		
		static ShaderProgram* FromGLSLTextFiles(const std::string& vertexPath, const std::string& fragmentPath);

	private:
		ShaderProgram() = default;

		void LoadFromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		GLuint CompileShader(GLenum type, const std::string& source);

	private:
		GLuint m_RendererID;
	};
}