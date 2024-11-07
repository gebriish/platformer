#include <core/application.h>
#include <game/editor_layer.h>

int main()
{
    Application app("~", 1024, 640, WINDOWFLAG_VSYNC);
    app.addLayer(std::make_shared<EditorLayer>());
    app.run();
}
