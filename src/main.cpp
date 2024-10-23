#include <core/application.h>
#include <game/game_layer.h>

int main()
{
    Application app("~", 640, 480, WINDOWFLAG_RESIZABLE);
    app.addLayer(std::make_shared<GameLayer>());
    app.run();
}
