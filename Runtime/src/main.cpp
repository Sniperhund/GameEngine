#include <Graphics/Renderer.h>

#include "Engine.h"

int main() {
    Project project{
        "Hello World!"
        "1.0.0"
    };

    Engine engine = Engine(1280, 720, project);

    engine.Run();

    return 0;
}
