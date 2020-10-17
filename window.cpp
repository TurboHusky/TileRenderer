#include "window.h"

#include <iostream>

namespace TileRender
{
	// Note: Can throw exceptions from constructor, however destructor is not called and cleanup must be done manually.
	Window::Window(const int width, const int height) : 
		m_width{ width }, 
		m_height{ height },
		m_world_position{ glm::uvec2(0u, 0u) }
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		m_window = glfwCreateWindow(width, height, "TileRenderer", NULL, NULL);
		if (m_window == NULL)
		{
			std::cout << "OpenGL::Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(m_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "OpenGL::Failed to initialize GLAD" << std::endl;
			glfwTerminate();
		}
	}

	Window::~Window()
	{
		glfwTerminate();
		std::cout << "Window Destructor, terminating window" << std::endl;
	}

	glm::uvec2 Window::world_position() const
	{
		return m_world_position;
	}

	bool Window::open() const
	{
		return !glfwWindowShouldClose(m_window);
	}

	void Window::refresh() const
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	void Window::processInput() const
	{
		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_window, true);

		if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		{
			m_world_position.y += 1;
		}
		if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_world_position.y -= 1;
		}
		if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		{
			m_world_position.x -= 1;
		}
		if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		{
			m_world_position.x += 1;
		}
		if (glfwGetKey(m_window, GLFW_KEY_C) == GLFW_PRESS)
		{
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}
}