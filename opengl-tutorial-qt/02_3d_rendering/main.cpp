#include <QGuiApplication>

#include "window.h"

int main(int argc, char *argv[])
{
    QGuiApplication app{argc, argv};

    Window window;
    window.resize(800, 600);
    window.show();

    return app.exec();
}




