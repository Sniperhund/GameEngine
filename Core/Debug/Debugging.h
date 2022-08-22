#pragma once

#include <iostream>

namespace GameEngine_Core
{
#ifdef DEBUG
#define DebugLog(message) std::cout << __FILE__ << " (" << __LINE__ << "): " << message << std::endl
#else
#define DebugLog(message)
#endif
}