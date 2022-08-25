#include "Renderer.h"

#include <format>
#include <imgui.h>

#include "../Debug/Debugging.h"
#include <assimp/DefaultLogger.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "../Model/ObjectsHandler.h"
#include "../UI/ImGuiHandler.h"

GLFWwindow* GameEngine_Core::Renderer::m_window;
GameEngine_Core::Camera GameEngine_Core::Renderer::m_camera(glm::vec3(0.0f, 0.0f, 3.0f));

int GameEngine_Core::Renderer::m_width = 0;
int GameEngine_Core::Renderer::m_height = 0;

float GameEngine_Core::Renderer::m_lastX = 0.0f;
float GameEngine_Core::Renderer::m_lastY = 0.0f;
bool GameEngine_Core::Renderer::m_firstMouse = true;

float GameEngine_Core::Renderer::m_deltaTime = 0.0f;
float GameEngine_Core::Renderer::m_lastFrame = 0.0f;
float GameEngine_Core::Renderer::m_nbFrames = 0.0f;

std::vector<std::function<void()>> GameEngine_Core::Renderer::m_gameLoops;
std::vector<std::reference_wrapper<GameEngine_Core::Shader>> GameEngine_Core::Renderer::m_shaders;

unsigned int GameEngine_Core::Renderer::AmountOfTriangles;
float GameEngine_Core::Renderer::nbFrames = 0;

bool GameEngine_Core::Renderer::m_useCamera = false;
bool GameEngine_Core::Renderer::m_drawObjects = true;

void GameEngine_Core::Renderer::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    m_width = width;
    m_height = height;
}

int GameEngine_Core::Renderer::CreateWindow(int width, int height, std::string title)
{
    if (!glfwInit())
    {
        DebugLog("GLFW instance was unable to be created");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
    glfwWindowHint(GLFW_SAMPLES, 8);
    
    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        DebugLog("GLFW window was unable to be created");
        return -1;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        DebugLog("GLAD instance was unable to be created");
        return -1;
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    m_width = width;
    m_height = height;

    m_lastX = static_cast<float>(width) / 2.0f;
    m_lastY = static_cast<float>(height) / 2.0f;

#ifdef DEBUG
    Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
    Assimp::LogStream* stderrStream = Assimp::LogStream::createDefaultStream(aiDefaultLogStream_STDERR);
    Assimp::DefaultLogger::get()->attachStream(stderrStream, Assimp::Logger::NORMAL | Assimp::Logger::DEBUGGING | Assimp::Logger::VERBOSE);
#endif

    glfwSwapInterval(0);
}

void GameEngine_Core::Renderer::Close(int code)
{
    Assimp::DefaultLogger::kill();
    glfwTerminate();
    exit(code);
}

double lastTime = glfwGetTime();

void GameEngine_Core::Renderer::UpdateDeltaTime()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    m_deltaTime = currentFrame - m_lastFrame;
    
    m_nbFrames++;
    if (currentFrame - lastTime >= 1.0f)
    {
        nbFrames = m_nbFrames;
        m_nbFrames = 0;
        lastTime += 1.0f;
    }

    m_lastFrame = currentFrame;
}

void GameEngine_Core::Renderer::AddGameLoopCallback(std::function<void()> callback)
{
    m_gameLoops.push_back(std::move(callback));
}

void GameEngine_Core::Renderer::StartGameLoop()
{
    ImGuiHandler::Init();
    while(!glfwWindowShouldClose(m_window))
    {
        Renderer::UpdateDeltaTime();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        UpdateShaders();

        if (m_drawObjects)
        {
            for (auto object : ObjectsHandler::GetObjects())
            {
                if (object.get().GetActive())
                    object.get().Draw();
            }
        }

        for (auto gameloop : m_gameLoops)
        {
            gameloop();
        }
        
        glfwSwapBuffers(Renderer::GetGLFWWindow());
        glfwPollEvents();

        AmountOfTriangles = 0;
    }

    Close(0);
}

void GameEngine_Core::Renderer::UpdateShaders()
{
    for (int i = 0; i < m_shaders.size(); i++)
    {
        m_shaders[i].get().Use();

        glm::mat4 projection = glm::perspective(glm::radians(Renderer::GetCamera().Fov), (float)m_width / (float)m_height, 0.1f, 100.0f);
        m_shaders[i].get().SetMat4("projection", projection);
        glm::mat4 view = Renderer::GetCamera().GetViewMatrix();
        m_shaders[i].get().SetMat4("view", view);

        m_shaders[i].get().SetVec3("viewPos", m_camera.Position);
        m_shaders[i].get().SetVec3("lightPos", glm::vec3(2.0f, 2.0f, 2.0f));
    }
}

void GameEngine_Core::Renderer::AddShader(Shader& shader)
{
    m_shaders.push_back(shader);
}

void GameEngine_Core::Renderer::SetUseCamera(bool active) { m_useCamera = active; }

void GameEngine_Core::Renderer::MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (!m_useCamera) return;
    
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (m_firstMouse)
    {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }

    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos;

    m_lastX = xpos;
    m_lastY = ypos;

    m_camera.ProcessMouseMovement(xoffset, yoffset);
}

GLFWwindow* GameEngine_Core::Renderer::GetGLFWWindow() { return m_window;}
GameEngine_Core::Camera& GameEngine_Core::Renderer::GetCamera() { return m_camera; }
float GameEngine_Core::Renderer::GetDeltaTime() { return m_deltaTime; }
std::vector<std::reference_wrapper<GameEngine_Core::Shader>>& GameEngine_Core::Renderer::GetShaders() { return m_shaders; }
bool GameEngine_Core::Renderer::GetUseCamera() { return m_useCamera; }