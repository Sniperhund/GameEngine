#include "ObjectsHandler.h"

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

std::vector<GameEngine_Core::Object> GameEngine_Core::ObjectsHandler::m_objects;

std::vector<GameEngine_Core::Object> GameEngine_Core::ObjectsHandler::GetObjects() { return m_objects; }
void GameEngine_Core::ObjectsHandler::AddObject(Object obj) { m_objects.emplace_back(obj); }