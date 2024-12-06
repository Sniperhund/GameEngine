#pragma once

#include <string>
#include <thread>

#define GLFW_INCLUDE_NONE
#include <condition_variable>
#include <queue>
#include <GLFW/glfw3.h>

#include "Scene/Scene.h"

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

	void PushFrame(Scene scene);

	GLFWwindow* getWindow();
private:
	GLFWwindow* m_window;

	// Render thread
	std::thread m_renderThread;
	std::atomic<bool> m_running;
	std::mutex m_sceneMutex;
	std::condition_variable m_frameCondition;

	std::queue<Scene> m_sceneQueue;
	void RenderLoop();
	void ProcessFrame(const Scene& scene);
};
