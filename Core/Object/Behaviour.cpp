#include "Behaviour.h"

void GameEngine_Core::Behaviour::_Start(std::reference_wrapper<Object> object)
{
    m_object = object;
}
