#pragma once

#include "opengl.h"

namespace TileRender
{
	class Window {
	private:
		int m_width{ 512 };
		int m_height{ 512 };

		GLFWwindow* m_window;

	public:
		Window(const int width, const int height);
		~Window();

		glm::uvec2 world_position() const; // TEMP, implement later.
		bool open() const;
		void refresh() const;
	};
}