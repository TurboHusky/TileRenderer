#pragma once

#include <glad/glad.h>
#include <GLFW/win64/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

template<typename T>
struct GLarrayWrapper {
	const GLsizeiptr size;
	const T* data;
	template<size_t s>
	GLarrayWrapper(const T(&d)[s]) : size{ s * sizeof(T) }, data{ d } {}
	~GLarrayWrapper() {}
};