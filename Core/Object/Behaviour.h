#pragma once
#include <functional>

#include "Object.h"

namespace GameEngine_Core
{
    class Behaviour
    {
    protected:
        std::reference_wrapper<Object> m_object;
    public:

        void _Start(std::reference_wrapper<Object> object);
        
        virtual void Start();
        virtual void Update();
    };
}
