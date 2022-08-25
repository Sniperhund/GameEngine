#include "Object.h"

// OBJECT
void GameEngine_Core::Object::_Init(std::string modelPath, std::string vertexShaderPath, std::string fragmentShaderPath,
                                    float x, float y, float z)
{
    m_model.Init(modelPath);
    m_shader.Init(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    Renderer::AddShader(m_shader);
    SetPosition(x, y, z);
    objectInformation.m_active = m_active;
    objectInformation.ConvertVec3ToFloat3(glm::vec3(x, y, z), objectInformation.m_position);
    objectInformation.m_modelPath = modelPath;
    objectInformation.m_fragmentShaderPath = fragmentShaderPath;
    objectInformation.m_vertexShaderPath = vertexShaderPath;
}

glm::vec3 GameEngine_Core::Object::GetPosition() const { return m_position; }
glm::vec3 GameEngine_Core::Object::GetScale() const { return m_scale; }
glm::vec3 GameEngine_Core::Object::GetRotation() const { return m_rotation; }
glm::vec4 GameEngine_Core::Object::GetColor() const { return m_color; }
bool GameEngine_Core::Object::GetActive() const { return m_active; }
std::string GameEngine_Core::Object::GetName() const { return m_name; }

void GameEngine_Core::Object::SetPosition(glm::vec3 pos) { m_position = pos; objectInformation.ConvertVec3ToFloat3(pos, objectInformation.m_position); }
void GameEngine_Core::Object::SetPosition(float x, float y, float z) { SetPosition(glm::vec3(x, y, z)); }
void GameEngine_Core::Object::SetScale(glm::vec3 scale) { m_scale = scale; objectInformation.ConvertVec3ToFloat3(scale, objectInformation.m_scale); }
void GameEngine_Core::Object::SetScale(float x, float y, float z) { SetScale(glm::vec3(x, y, z)); }
void GameEngine_Core::Object::SetRotation(glm::vec3 rotation) { m_rotation = rotation; objectInformation.ConvertVec3ToFloat3(rotation, objectInformation.m_rotation); }
void GameEngine_Core::Object::SetRotation(float x, float y, float z) { SetRotation(glm::vec3(x, y, z)); }
void GameEngine_Core::Object::SetActive(bool state) { m_active = state; objectInformation.m_active = state; }
void GameEngine_Core::Object::SetName(std::string name) { m_name = name; objectInformation.m_name = name; }
void GameEngine_Core::Object::SetColor(glm::vec4 color) { m_color = color; objectInformation.ConvertVec4ToFloat4(color, objectInformation.m_color); }
void GameEngine_Core::Object::SetColor(float r, float g, float b, float a) { SetColor(glm::vec4(r, g, b, a)); }
void GameEngine_Core::Object::SetColorRGB(float r, float g, float b, float a) { SetColor(glm::vec4(r/255, g/255, b/255, a/255)); }

void GameEngine_Core::Object::Init(std::string modelPath, std::string shaderPath, std::string name, glm::vec3 pos)
{
    Init(modelPath, std::format("{}.vert", shaderPath),
        std::format("{}.frag", shaderPath), name, pos.x, pos.y, pos.z);
}

void GameEngine_Core::Object::Init(std::string modelPath, std::string shaderPath, std::string name, float x, float y,
    float z)
{
    Init(modelPath, std::format("{}.vert", shaderPath),
        std::format("{}.frag", shaderPath), name, x, y, z);
}

void GameEngine_Core::Object::Init(std::string modelPath, std::string vertexShaderPath, std::string fragmentShaderPath,
                                   std::string name, float x, float y, float z)
{
    _Init(modelPath, vertexShaderPath, fragmentShaderPath, x, y, z);
    m_name = name;
    objectInformation.m_name = name;
}

void GameEngine_Core::Object::Draw()
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

