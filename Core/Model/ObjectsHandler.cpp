#include "ObjectsHandler.h"

std::vector<std::reference_wrapper<GameEngine_Core::Object>> GameEngine_Core::ObjectsHandler::m_objects;

std::vector<std::reference_wrapper<GameEngine_Core::Object>> GameEngine_Core::ObjectsHandler::GetObjects() { return m_objects; }
void GameEngine_Core::ObjectsHandler::AddObject(std::reference_wrapper<Object> obj) { m_objects.emplace_back(obj); }