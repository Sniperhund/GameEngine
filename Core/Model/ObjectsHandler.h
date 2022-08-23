#pragma once

#include "Object.h"

namespace GameEngine_Core
{
    class ObjectsHandler
    {
        static vector<std::reference_wrapper<Object>> m_objects;
    public:
        static std::vector<std::reference_wrapper<Object>> GetObjects();
        static void AddObject(std::reference_wrapper<Object> obj);
    };
}
