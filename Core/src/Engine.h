//
// Created by Lucas Täkker on 12/4/24.
//

#pragma once

#include "Graphics/Renderer.h"
#include "Project.h"

/**
* Engine class
*
* This should contain the renderer, active scene and project information, with utility functions for switching scene etc.
* This should not contain any information only relevant to the Editor or Runtime
*/
class Engine {
public:
	Renderer renderer;
	// Scene scene;
	Project project;

	Engine(int width, int height, Project& project);

	virtual void Run();
};