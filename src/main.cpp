#include "OpenGLEngine.h"

int main()
{
    OpenGLEngine engine;

    engine.init();

    engine.mainEventLoop();

    engine.shutdown();

    return 0;
}