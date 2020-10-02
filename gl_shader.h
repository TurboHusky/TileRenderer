#pragma once

#include "opengl.h"

class Shader
{
private:
	unsigned int shader_ID{ 0 };
public:
	//Shader();
	Shader(const char* shader_path, const int shader_type);
	~Shader();

	void attach(const unsigned int program_ID) const;
};

class Program
{
private:
	unsigned int program_ID{ 0 };
public:
	Program(const char* vertex_shader_path, const char* fragment_shader_path);
	//Program(const Program& other);
	//Program& operator=(Program&& other);
	~Program();

	void use(void) const;
	void bind_uniform_block(const char* u_id, GLuint index) const;
	GLint get_ubo_size(GLint binding_index) const;

	void setUniform_vec2_u(const char* prop, const glm::uvec2 vec) const;
	void setUniform_vec4_u(const char* prop, const glm::uvec4 vec) const;
	void setUniform_vec2_f(const char* prop, const glm::vec2 vec) const;
	void setUniform_vec4_f(const char* prop, const glm::vec4 vec) const;
};