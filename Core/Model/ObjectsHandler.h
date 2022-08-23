#pragma once
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

#include "Object.h"

namespace GameEngine_Core
{
    class ObjectsHandler
    {
        static vector<Object> m_objects;
    public:
        static std::vector<Object> GetObjects();
        static void AddObject(Object obj);
    };
}
