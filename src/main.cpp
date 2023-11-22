#include "OpenGLEngine.h"

int main(void)
{
    OpenGLEngine engine;

    engine.init();

    engine.mainEventLoop();

    engine.shutdown();

    exit(EXIT_SUCCESS);
}