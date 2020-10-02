#include "window.h"

#include <iostream>

// Note: Can throw exceptions from constructor, however destructor is not called and cleanup must be done manually.
Window::Window(const int width, const int height) : SCREEN_WIDTH{ width }, SCREEN_HEIGHT{ height }
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(width, height, "TileRenderer", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "OpenGL::Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

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
	return glm::uvec2(69.0, 85.0);
}

bool Window::open() const
{
	return !glfwWindowShouldClose(window);
}

void Window::refresh() const
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}