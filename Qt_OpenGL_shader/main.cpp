#include <QApplication>
#include <QSurfaceFormat>
#include "ObjectWindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(5);

    ObjectWindow window;
    window.setFormat(format);
    window.show();
    window.setAnimating(true);
    return app.exec();
}
