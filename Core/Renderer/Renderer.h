#pragma once

#include <functional>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Classes/Camera.h"
#include "../Classes/Shader.h"

namespace GameEngine_Core {
    class Renderer
    {
        static int m_width;
        static int m_height;
        
        static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    
        static Camera m_camera;
        static GLFWwindow* m_window;
    
        static float m_lastX;
        static float m_lastY;
        static bool m_firstMouse;
    
        static float m_deltaTime;
        static float m_lastFrame;
    
        static std::vector<std::function<void()>> m_gameLoops;
        static std::vector<std::reference_wrapper<Shader>> m_shaders;
    
        static float m_nbFrames;
    
        static bool m_useCamera;
        
        static void UpdateShaders();
    public:
        static unsigned int AmountOfTriangles;
        static float nbFrames;
        static bool m_drawObjects;
        
        static int CreateWindow(int width, int height, std::string title);
        static void Close(int code);
        static void UpdateDeltaTime();
    
        static void AddGameLoopCallback(std::function<void()> callback);
        static void StartGameLoop();
    
        static void AddShader(Shader& shader);
    
        static void SetUseCamera(bool active);
        
        static void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);
        
        static GLFWwindow* GetGLFWWindow();
        static Camera& GetCamera();
        static float GetDeltaTime();
        static std::vector<std::reference_wrapper<Shader>>& GetShaders();
        static bool GetUseCamera();
    };
}