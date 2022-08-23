#include "ObjectsHandler.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "../Debug/Debugging.h"

#include "../Util/VectContainer.hpp"

#define MAX_OBJECTS 5

std::vector<std::reference_wrapper<GameEngine_Core::Object>> GameEngine_Core::ObjectsHandler::m_objects;
std::vector<GameEngine_Core::Object> GameEngine_Core::ObjectsHandler::m_savedObjects(MAX_OBJECTS);

int GameEngine_Core::ObjectsHandler::index = 0;

std::vector<std::reference_wrapper<GameEngine_Core::Object>> GameEngine_Core::ObjectsHandler::GetObjects() { return m_objects; }
void GameEngine_Core::ObjectsHandler::AddObject(std::reference_wrapper<Object> obj) { m_objects.emplace_back(obj); }

void GameEngine_Core::ObjectsHandler::Save()
{
    VectContainer<ObjectInformation> objectInformations;
    
    std::ofstream ofs("objects.bin");
    boost::archive::text_oarchive ar(ofs);

    for (auto object : m_objects)
    {
        objectInformations.elements.push_back(object.get().objectInformation);
    }

    ar &objectInformations;

    ofs.close();

    DebugLog("Done saving!");
}

void GameEngine_Core::ObjectsHandler::Load()
{
    VectContainer<ObjectInformation> objectInformations;
    
    std::ifstream ifs("objects.bin");
    boost::archive::text_iarchive ar(ifs);

    ar &objectInformations;

    for (auto object : objectInformations.elements)
    {
        m_savedObjects[index].Init(object.m_modelPath, object.m_vertexShaderPath, object.m_fragmentShaderPath,
            object.m_name, object.m_position[0], object.m_position[1], object.m_position[2]);
        m_savedObjects[index].SetScale(object.m_scale[0], object.m_scale[1], object.m_scale[2]);
        m_savedObjects[index].SetRotation(object.m_rotation[0], object.m_rotation[1], object.m_rotation[2]);
        m_savedObjects[index].SetColor(object.m_color[0], object.m_color[1], object.m_color[2], object.m_color[3]);
        m_savedObjects[index].SetActive(object.m_active);

        m_objects.emplace_back(m_savedObjects[index]);

        index++;
    }
}
