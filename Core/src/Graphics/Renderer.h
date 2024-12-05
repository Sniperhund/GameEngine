#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

/**
 * Note to self
 *
 * For multithreading I could maybe pass a copy of scene to Frame()
 * and run most of the Renderer on another thread and therefore also bgfx
 *
 * So everything other than the outward API is running on a render thread
 */
class Renderer {
public:
	Renderer(int width, int height, std::string title);

	~Renderer();

	void Frame();

	GLFWwindow* getWindow();
private:
	GLFWwindow* m_window;
};
