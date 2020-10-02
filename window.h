#pragma once

#include "opengl.h"

class Window {
private:
	int SCREEN_WIDTH{ 512 };
	int SCREEN_HEIGHT{ 512 };

	GLFWwindow* window;

public:
	Window(const int width, const int height);
	~Window();

	glm::uvec2 world_position() const; // TEMP, implement later.
	bool open() const;
	void refresh() const;
};