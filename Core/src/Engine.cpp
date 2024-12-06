//
// Created by Lucas Täkker on 12/4/24.
//

#include "Engine.h"

Engine::Engine(int width, int height, Project &project) : renderer(width, height, project.name), project(project) { }

void Engine::Run() {
	while (!glfwWindowShouldClose(renderer.getWindow())) {
		glfwPollEvents();

		renderer.PushFrame(Scene());
	}
}
