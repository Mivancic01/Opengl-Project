#include "Engine.h"

int main()
{
    Engine* app = Engine::getInstance();
    app->init();
    app->run();

    return 0;
}