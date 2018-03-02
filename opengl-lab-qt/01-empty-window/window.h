#pragma once

#include "openglwindow.h"

QT_BEGIN_NAMESPACE
class QKeyEvent;
QT_END_NAMESPACE

class Window : public OpenGLWindow
{
    Q_OBJECT

public:
    Window();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

    void keyPressEvent(QKeyEvent *ev) Q_DECL_OVERRIDE;

private:
    void printOpenGlExtraInfo();
};
