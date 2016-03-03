#include <QApplication>
#include <QSurfaceFormat>
#include "ObjectWindow.h"
#include "videoplayer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    VideoPlayer player;
//    player.setGeometry(750,100,320,240);
//    player.show();

    QSurfaceFormat format;
    format.setSamples(5);

    ObjectWindow window;
    window.setFormat(format);
    window.show();
    window.setAnimating(true);
    return app.exec();
}
