#pragma once

#include <format>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_stdlib.h>

#include "../Renderer/Renderer.h"

namespace GameEngine_Core
{
    class ImGuiHandler
    {
#define MAX_OBJECTS 5

        inline static bool m_showNewObjectMenu = false;
        inline static bool m_showHierarchyMenu = false;
        inline static bool m_showMetricsMenu = false;
        inline static bool m_showEngineMenu = false;

        inline static int working_object = 0;

        inline static bool m_showImGuiExamples = false;

        inline static std::vector<Object> m_objects;

        inline static char m_modelPath[128] = "";
        inline static char m_shaderPath[128] = "";
        inline static char m_name[128] = "";
        inline static float m_pos[3] = {0, 0, 0};
    public:
        static void Init()
        {
            m_objects = std::vector<Object>(MAX_OBJECTS);
            Renderer::AddGameLoopCallback(Render);

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.WantCaptureMouse = true;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

            ImGui::StyleColorsDark();
        
            ImGui_ImplGlfw_InitForOpenGL(Renderer::GetGLFWWindow(), true);
            ImGui_ImplOpenGL3_Init("#version 330");
        }
    
        static void Render()
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (m_showNewObjectMenu) ShowNewObject(&m_showNewObjectMenu);
            else
            {
                strcpy_s(m_modelPath, "");
                strcpy_s(m_shaderPath, "");
                strcpy_s(m_name, "");
                m_pos[0] = 0;
                m_pos[1] = 0;
                m_pos[2] = 0;
            }
            if (m_showHierarchyMenu) ShowHierarchy(&m_showHierarchyMenu);
            if (m_showMetricsMenu) ShowMetrics(&m_showMetricsMenu);
            if (m_showEngineMenu) ShowEngine(&m_showEngineMenu);
            if (m_showImGuiExamples) ImGui::ShowDemoWindow(&m_showImGuiExamples);

            ImGui::BeginMainMenuBar();
            if (ImGui::BeginMenu("Windows"))
            {
                ImGui::MenuItem("Show Engine", nullptr, &m_showEngineMenu);
                ImGui::MenuItem("Show Hierarchy", nullptr, &m_showHierarchyMenu);
                ImGui::MenuItem("Show Metrics", nullptr, &m_showMetricsMenu);

                ImGui::EndMenu();
            }
#ifdef DEBUG
            if (ImGui::BeginMenu("Engine Development"))
            {
                ImGui::MenuItem("Show ImGui Examples/Demos", nullptr, &m_showImGuiExamples);

                ImGui::EndMenu();
            }
#endif
            ImGui::EndMainMenuBar();
        
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        static void ShowEngine(bool *p_open)
        {
            if (!ImGui::Begin("Engine", p_open, ImGuiWindowFlags_MenuBar))
            {
                ImGui::End();
                return;
            }

            ImGui::End();
        }
        static void ShowMetrics(bool* p_open)
        {
            if (!ImGui::Begin("Metrics", p_open))
            {
                ImGui::End();
                return;
            }

            ImGui::Text(std::format("Application average {} ms/frame ({} FPS)", 1000.0f / Renderer::nbFrames, Renderer::nbFrames).c_str());
            ImGui::Text(std::format("Amount of triangles in scene: {}", std::to_string(Renderer::AmountOfTriangles)).c_str());

            ImGui::End();
        }
        static void ShowNewObject(bool* p_open)
        {
            if (!ImGui::Begin("New Object", p_open))
            {
                ImGui::End();
                return;
            }
            
            ImGui::InputText("Model path", m_modelPath, IM_ARRAYSIZE(m_modelPath));

            ImGui::InputText("Shader path", m_shaderPath, IM_ARRAYSIZE(m_shaderPath));
            
            ImGui::InputText("Name", m_name, IM_ARRAYSIZE(m_name));
            
            ImGui::InputFloat3("Position", m_pos);

            ImGui::Spacing();
            if (ImGui::Button("Submit"))
            {
                Renderer::m_drawObjects = false;
                m_objects[working_object].Init(std::format("Assets/{}", m_modelPath),
                    std::format("Shader/{}", m_shaderPath), m_name, m_pos[0], m_pos[1], m_pos[2]);
                ObjectsHandler::AddObject(m_objects[working_object]);
                m_showNewObjectMenu = false;
                Renderer::m_drawObjects = true;
                working_object++;
                strcpy_s(m_modelPath, "");
                strcpy_s(m_shaderPath, "");
                strcpy_s(m_name, "");
                m_pos[0] = 0;
                m_pos[1] = 0;
                m_pos[2] = 0;
            }
        
            ImGui::End();
        }
        static void ShowHierarchy(bool* p_open)
        {
            if (!ImGui::Begin("Hierarchy", p_open, ImGuiWindowFlags_MenuBar))
            {
                ImGui::End();
                return;
            }

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("Menu"))
                {
                    ImGui::MenuItem("New Object", nullptr, &m_showNewObjectMenu);
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
        
            ImGui::Spacing();
        
            for (auto object : ObjectsHandler::GetObjects())
            {
                if(ImGui::TreeNode(object.get().GetName().c_str()))
                {
                    ImGui::Text("General Settings");
                    std::string name = object.get().GetName();
                    if (ImGui::InputText("Name", &name, ImGuiInputTextFlags_EnterReturnsTrue))
                        object.get().SetName(name);
                
                    ImGui::Text("Transform");
                    glm::vec3 _pos = object.get().GetPosition();
                    float pos[3] = {_pos.x, _pos.y, _pos.z};
                    ImGui::InputFloat3("Position", pos);
                    object.get().SetPosition(pos[0], pos[1], pos[2]);

                    glm::vec3 _scale = object.get().GetScale();
                    float scale[3] = {_scale.x, _scale.y, _scale.z};
                    ImGui::InputFloat3("Scale", scale);
                    object.get().SetScale(scale[0], scale[1], scale[2]);

                    glm::vec3 _rotation = object.get().GetRotation();
                    float rotation[3] = {_rotation.x, _rotation.y, _rotation.z};
                    ImGui::InputFloat3("Rotation", rotation);
                    object.get().SetRotation(rotation[0], rotation[1], rotation[2]);

                    ImGui::Text("Rendering");
                    bool active = object.get().GetActive();
                    ImGui::Checkbox("Active", &active);
                    object.get().SetActive(active);

                    glm::vec4 _col = object.get().GetColor();
                    float col[4] = {_col.x, _col.y, _col.z, _col.w};
                    ImGui::ColorPicker4("Color", col, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
                    object.get().SetColor(glm::vec4(col[0], col[1], col[2], col[3]));
                
                    ImGui::TreePop();
                }
            }

            ImGui::End();
        }
    };
}
