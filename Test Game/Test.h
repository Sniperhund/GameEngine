#pragma once

#include <Engine.h>

class Test : public GameEngine_Core::Behaviour
{
public:
    void Start() override
    {
        DebugLog("Testing");
    }
};