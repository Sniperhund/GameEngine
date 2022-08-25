#pragma once
#include <format>
#include <string>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <boost/serialization/serialization.hpp>

#include "../Model/Model.h"

namespace GameEngine_Core
{
    struct ObjectInformation
    {
        float m_position[3] = {0, 0, 0};
        float m_scale[3] = {1, 1, 1};
        float m_rotation[3] = {0, 0, 0};

        float m_color[4] = {0, 0, 0, 0};

        std::string m_modelPath;
        std::string m_vertexShaderPath;
        std::string m_fragmentShaderPath;
        std::string m_name;

        bool m_active;

        void ConvertVec3ToFloat3(glm::vec3 vec, std::reference_wrapper<float[3]> float3)
        {
            float3.get()[0] = vec.x;
            float3.get()[1] = vec.y;
            float3.get()[2] = vec.z;
        }

        void ConvertVec4ToFloat4(glm::vec4 vec, std::reference_wrapper<float[4]> float3)
        {
            float3.get()[0] = vec.x;
            float3.get()[1] = vec.y;
            float3.get()[2] = vec.z;
            float3.get()[3] = vec.w;
        }
        
        friend class boost::serialization::access;
        template <class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar &m_position &m_position &m_scale &m_rotation &m_color &m_modelPath &m_vertexShaderPath &m_fragmentShaderPath &m_active &m_name;  // Simply serialize the data members
        }
    };
    
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
        
        void _Init(std::string modelPath, std::string vertexShaderPath, std::string fragmentShaderPath, float x, float y, float z);
    public:
        ObjectInformation objectInformation;
        
        glm::vec3 GetPosition() const;
        glm::vec3 GetScale() const;
        glm::vec3 GetRotation() const;
        glm::vec4 GetColor() const;
        bool GetActive() const;
        std::string GetName() const;

        void SetPosition(glm::vec3 pos);
        void SetPosition(float x, float y, float z);
        void SetScale(glm::vec3 scale);
        void SetScale(float x, float y, float z);
        void SetRotation(glm::vec3 rotation);
        void SetRotation(float x, float y, float z);
        void SetActive(bool state);
        void SetName(std::string name);
        void SetColor(glm::vec4 color);
        void SetColor(float r, float g, float b, float a);
        void SetColorRGB(float r, float g, float b, float a);

        void Init(std::string modelPath, std::string shaderPath, std::string name, glm::vec3 pos);
        void Init(std::string modelPath, std::string shaderPath, std::string name, float x, float y, float z);
        void Init(std::string modelPath, std::string vertexShaderPath, std::string fragmentShaderPath, std::string name, float x, float y, float z);

        void Draw();
    };
}