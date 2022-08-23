#pragma once

#include "../Object/Object.h"

namespace GameEngine_Core
{
    class ObjectsHandler
    {
        static std::vector<std::reference_wrapper<Object>> m_objects;

        static std::vector<Object> m_savedObjects;

        static int index;
    public:
        static std::vector<std::reference_wrapper<Object>> GetObjects();
        static void AddObject(std::reference_wrapper<Object> obj);

        static void Save();
        static void Load();
    };
}
