#include <core/application.h>
#include <game/game_layer.h>

int main()
{
    Application app("~", 800, 500, WINDOWFLAG_NONE);
    app.addLayer(std::make_shared<GameLayer>());
    app.run();
}

