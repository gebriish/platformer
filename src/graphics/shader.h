#pragma once

struct Shader {
	unsigned int ID;
};

void load_glsl_shader(const char* vertexPath, const char* fragmentPath, Shader& program);
void use_shader_program(const Shader& program);
void delete_shader_program(const Shader& program);

void shader_upload_int(const Shader& program, const char* name, int v);
void shader_upload_float(const Shader& program, const char* name, float v);
void shader_upload_vec2(const Shader& program, const char* name, float x, float y);
void shader_upload_vec4(const Shader& program, const char* name, float x, float y, float z, float w);