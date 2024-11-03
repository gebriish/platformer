#include <core/application.h>
#include <game/editor_layer.h>

int main()
{
    Application app("~", 640, 480, WINDOWFLAG_UNDECORATED);
    app.addLayer(std::make_shared<EditorLayer>());
    app.run();
}
