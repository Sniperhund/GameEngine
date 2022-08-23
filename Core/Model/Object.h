#pragma once
#include <format>
#include <string>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Model.h"

#include "../Renderer/Renderer.h"

namespace GameEngine_Core
{
    class Object
    {
    private:
        glm::vec3 m_position = glm::vec3(0);
        glm::vec3 m_scale = glm::vec3(1);
        glm::vec3 m_rotation = glm::vec3(0);

        glm::vec4 m_color = glm::vec4(0);

        Model m_model;
        Shader m_shader;
    
        bool m_active = true;

        std::string m_name = "";

        void _Init(std::string modelPath, std::string vertexShaderPath, std::string fragmentShaderPath, float x, float y, float z)
        {
            m_model.Init(modelPath);
            m_shader.Init(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
            Renderer::AddShader(m_shader);
            SetPosition(x, y, z);
        }
    public:
        glm::vec3 GetPosition() const { return m_position; }
        glm::vec3 GetScale() const { return m_scale; }
        glm::vec3 GetRotation() const { return m_rotation; }
        glm::vec4 GetColor() const { return m_color; }
        bool GetActive() const { return m_active; }
        std::string GetName() { return m_name; }

        void SetPosition(glm::vec3 pos) { m_position = pos; }
        void SetPosition(float x, float y, float z) { m_position = glm::vec3(x, y, z); }
        void SetScale(glm::vec3 scale) { m_scale = scale; }
        void SetScale(float x, float y, float z) { m_scale = glm::vec3(x, y, z); }
        void SetRotation(glm::vec3 rotation) { m_rotation = rotation; }
        void SetRotation(float x, float y, float z) { m_rotation = glm::vec3(x, y, z); }
        void SetActive(bool state) { m_active = state; }
        void SetName(std::string name) { m_name = name; }
        void SetColor(glm::vec4 color) { m_color = color; }

        void Init(std::string modelPath, std::string shaderPath, std::string name, glm::vec3 pos)
        {
            _Init(modelPath, std::format("{}.vert", shaderPath), std::format("{}.frag", shaderPath), pos.x, pos.y, pos.z);
            m_name = name;
        }
        void Init(std::string modelPath, std::string shaderPath, std::string name, float x, float y, float z)
        {
            _Init(modelPath, std::format("{}.vert", shaderPath), std::format("{}.frag", shaderPath), x, y, z);
            m_name = name;
        }
    
        void Draw()
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, m_position);
            model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
            model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
            model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
            model = glm::scale(model, m_scale);

            m_shader.Use();
            m_shader.SetMat4("model", model);
            m_shader.SetVec4("custom_color", m_color);
            m_model.Draw(m_shader);
        }
    };
}