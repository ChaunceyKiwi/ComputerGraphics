#include <QtCore>
#include <QDebug>
#include "window.h"

class ThreadDraw : public QThread
{
public:
    ThreadDraw();
    QSurfaceFormat format;
    Window window;
};

// create window and draw models
ThreadDraw::ThreadDraw()
{
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3);

    // Set the window up
    window.setFormat(format);
    window.resize(QSize(800, 600));
    window.show();
}
