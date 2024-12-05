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

#include "imgui/imgui_impl_bgfx.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>

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
	//init.resolution.reset = BGFX_RESET_VSYNC;

	if (!bgfx::init(init)) {
		std::cerr << "Failed to initialize bgfx" << std::endl;
		glfwDestroyWindow(m_window);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	bgfx::setDebug(BGFX_DEBUG_STATS);

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_Implbgfx_Init(0);

	switch (bgfx::getRendererType()) {
		case bgfx::RendererType::OpenGL:
			ImGui_ImplGlfw_InitForOpenGL(m_window, true);
		case bgfx::RendererType::Vulkan:
			ImGui_ImplGlfw_InitForOther(m_window, true);
		default:
			ImGui_ImplGlfw_InitForOther(m_window, true);
	}
}

Renderer::~Renderer() {
}

void Renderer::Frame() {
	bgfx::touch(0);

	glfwPollEvents();

	bgfx::dbgTextClear();
	bgfx::dbgTextPrintf(0, 0, 0x0f, "Hello, World!");

	ImGui_Implbgfx_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());

	bgfx::frame();
}

GLFWwindow* Renderer::getWindow() {
	return m_window;
}
