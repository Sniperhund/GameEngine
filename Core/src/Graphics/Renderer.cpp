#include "Renderer.h"

#include <iostream>
#include <cstdlib>

#include <bgfx/bgfx.h>
#include <bx/bx.h>

#if BX_PLATFORM_LINUX
#	define GLFW_EXPOSE_NATIVE_WAYLAND
#	define GLFW_EXPOSE_NATIVE_X11
#	define GLFW_EXPOSE_NATIVE_GLX
#elif BX_PLATFORM_OSX
#	define GLFW_EXPOSE_NATIVE_COCOA
#	define GLFW_EXPOSE_NATIVE_NSGL
#elif BX_PLATFORM_WINDOWS
#	define GLFW_EXPOSE_NATIVE_WIN32
#	define GLFW_EXPOSE_NATIVE_WGL
#endif // BX_PLATFORM_
#include <GLFW/glfw3native.h>

Renderer::Renderer(int width, int height, std::string title) {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!m_window) {
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	bgfx::Init init;
#if BX_PLATFORM_LINUX
	init.platformData.ndt = glfwGetX11Display();
	init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(m_window);
#elif BX_PLATFORM_OSX
	init.platformData.nwh = glfwGetCocoaWindow(m_window);
#elif BX_PLATFORM_WINDOWS
	init.platformData.nwh = glfwGetWin32Window(m_window);
#endif // BX_PLATFORM_

	init.resolution.width = width;
	init.resolution.height = height;
	init.resolution.reset = BGFX_RESET_VSYNC;

	if (!bgfx::init(init)) {
		std::cerr << "Failed to initialize bgfx" << std::endl;
		glfwDestroyWindow(m_window);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	bgfx::setDebug(BGFX_DEBUG_TEXT);

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
}

Renderer::~Renderer() {
}

void Renderer::Frame() {
	bgfx::touch(0);

	bgfx::dbgTextClear();
	bgfx::dbgTextPrintf(0, 0, 0x0f, "Hello, World!");

	bgfx::frame();

	glfwPollEvents();
}

GLFWwindow* Renderer::getWindow() {
	return m_window;
}
