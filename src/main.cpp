#include <core/application.h>
#include <game/main_layer.h>

int main()
{
    Application app("~", 800, 500, WINDOWFLAG_UNDECORATED);
    app.addLayer(std::make_shared<MainLayer>());
    app.run();
}
