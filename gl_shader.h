#pragma once

#include "opengl.h"

namespace GLRender
{
	class Shader
	{
	private:
		unsigned int m_shader_ID;
	public:
		Shader(const char* shader_path, const GLint shader_type);
		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&) = delete;
		~Shader();

		void attach(const unsigned int program_ID) const;
	};

	class Program
	{
	public: // DEBUG, MAKE PRIVATE
		unsigned int m_program_ID;
	public:
		Program(const char* vertex_shader_path, const char* fragment_shader_path);
		Program(const Program&) = delete;
		Program(Program&&) = delete;
		Program& operator=(const Program&) = delete;
		Program& operator=(Program&&) = delete;
		~Program();

		void use(void) const;
		void bind_uniform_block(const char* u_id, GLuint index) const;
		GLint get_ubo_size(GLint binding_index) const;

		void setUniform_vec2_u(const char* prop, const glm::uvec2 vec) const;
		void setUniform_vec4_u(const char* prop, const glm::uvec4 vec) const;
		void setUniform_vec2_f(const char* prop, const glm::vec2 vec) const;
		void setUniform_vec4_f(const char* prop, const glm::vec4 vec) const;
	};
}