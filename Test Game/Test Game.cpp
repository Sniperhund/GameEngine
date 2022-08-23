#include "Engine.h"
#include "Test.h"

using namespace GameEngine_Core;

void ProcessInput(GLFWwindow *window);
void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void GameLoop()
{
    ProcessInput(Renderer::GetGLFWWindow());
}

int main(int argc, char* argv[])
{
    Renderer::CreateWindow(1280, 720, "Game Engine");
    
    Renderer::AddGameLoopCallback(GameLoop);
    
    glfwSetCursorPosCallback(Renderer::GetGLFWWindow(), Renderer::MouseCallback);
    glfwSetKeyCallback(Renderer::GetGLFWWindow(), InputCallback);

    Object box;
    box.Init("Assets/Test.fbx", "Shader/Shader", "Something", 0, 0, 0);
    Test test;
    box.AddBehaviour(test);
    ObjectsHandler::AddObject(box);

    Renderer::StartGameLoop();
}

void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
        if (glfwGetInputMode(Renderer::GetGLFWWindow(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
        {
            glfwSetInputMode(Renderer::GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            Renderer::SetUseCamera(false);
        } else
        {
            glfwSetInputMode(Renderer::GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            Renderer::SetUseCamera(true);
        }
}

void ProcessInput(GLFWwindow *window)
{
    if (!Renderer::GetUseCamera()) return;
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Renderer::GetCamera().ProcessKeyboard(FORWARD, Renderer::GetDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Renderer::GetCamera().ProcessKeyboard(BACKWARD, Renderer::GetDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Renderer::GetCamera().ProcessKeyboard(LEFT, Renderer::GetDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Renderer::GetCamera().ProcessKeyboard(RIGHT, Renderer::GetDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        Renderer::GetCamera().ProcessKeyboard(UP, Renderer::GetDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        Renderer::GetCamera().ProcessKeyboard(DOWN, Renderer::GetDeltaTime());
}