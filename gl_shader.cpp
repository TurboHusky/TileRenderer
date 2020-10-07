#include "gl_shader.h"

#include <string>
#include <fstream>
#include <sstream>

namespace GLRender
{
	static std::string load_shader_code(const char* path)
	{
		std::stringstream stream;

		try
		{
			std::ifstream file;
			file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			file.open(path);
			stream << file.rdbuf();
			file.close();

			// file.setstate(std::ios::badbit); // error testing
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		return stream.str();
	}

	static GLuint compile_shader(const char* shader_code, const GLint shader_type)
	{
		GLuint ID{ 0 };
		GLint success{ 0 };
		GLchar infoLog[1024];

		ID = glCreateShader(shader_type);
		glShaderSource(ID, 1, &shader_code, NULL);
		glCompileShader(ID);
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 1024, NULL, infoLog);
			std::cout << "ERROR::" << shader_type << "::COMPILATION_ERROR of type: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
		return ID;
	}

	Shader::Shader(const char* shader_path, const GLint shader_type) : m_shader_ID{ 0 }
	{
		std::string shaderCode = load_shader_code(shader_path);
		m_shader_ID = compile_shader(shaderCode.c_str(), shader_type);
	}

	Shader::~Shader()
	{
		glDeleteShader(m_shader_ID);
		std::cout << "Shader Destructor, ID: " << m_shader_ID << std::endl;
	}

	void Shader::attach(const unsigned int program_ID) const
	{
		glAttachShader(program_ID, m_shader_ID);
	}

	Program::Program(const char* vertex_shader_path, const char* fragment_shader_path)
	{
		Shader vertex_shader(vertex_shader_path, GL_VERTEX_SHADER);
		Shader fragment_shader(fragment_shader_path, GL_FRAGMENT_SHADER);

		GLint success;
		GLchar infoLog[1024];

		m_program_ID = glCreateProgram();
		vertex_shader.attach(m_program_ID);
		fragment_shader.attach(m_program_ID);
		glLinkProgram(m_program_ID);
		glGetProgramiv(m_program_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_program_ID, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM::LINKING_ERROR of type: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}

	Program::~Program()
	{
		std::cout << "Shader Program Destructor, ID: " << m_program_ID << std::endl;
		glDeleteProgram(m_program_ID);
	}

	void Program::use(void) const
	{
		glUseProgram(m_program_ID);
	}

	void Program::bind_uniform_block(const char* u_id, GLuint index) const
	{
		GLuint ubo_index = glGetUniformBlockIndex(m_program_ID, u_id);
		if (ubo_index != GL_INVALID_INDEX)
			glUniformBlockBinding(m_program_ID, ubo_index, index);
		else
			std::cout << "ERROR::PROGRAM::INVALID_BINDING_ID" << std::endl;
	}

	GLint Program::get_ubo_size(GLint binding_index) const
	{
		GLint out{ 0 };
		glGetActiveUniformBlockiv(m_program_ID, binding_index, GL_UNIFORM_BLOCK_DATA_SIZE, &out);
		return out;
	}

	void Program::setUniform_vec2_u(const char* prop, const glm::uvec2 vec) const
	{
		int uniform_ID = glGetUniformLocation(m_program_ID, prop);
		glUniform2ui(uniform_ID, vec.x, vec.y);
	}

	void Program::setUniform_vec4_u(const char* prop, const glm::uvec4 vec) const
	{
		int uniform_ID = glGetUniformLocation(m_program_ID, prop);
		glUniform4ui(uniform_ID, vec.x, vec.y, vec.z, vec.w);
	}

	void Program::setUniform_vec2_f(const char* prop, const glm::vec2 vec) const
	{
		int uniform_ID = glGetUniformLocation(m_program_ID, prop);
		glUniform2f(uniform_ID, vec.x, vec.y);
	}

	void Program::setUniform_vec4_f(const char* prop, const glm::vec4 vec) const
	{
		int uniform_ID = glGetUniformLocation(m_program_ID, prop);
		glUniform4f(uniform_ID, vec.x, vec.y, vec.z, vec.w);
	}
}