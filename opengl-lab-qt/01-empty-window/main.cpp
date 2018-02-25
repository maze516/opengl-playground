#include <QGuiApplication>
#include "window.h"

int main(int argc, char *argv[])
{
    QGuiApplication app{argc, argv};

#ifdef QT_OPENGL_DESKTOP
    Window window{QSurfaceFormat::OpenGL, 3, 3};
#else
    Window window{};
#endif
    window.show();

    return app.exec();
}
