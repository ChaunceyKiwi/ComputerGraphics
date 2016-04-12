#include <QtCore>
#include <QDebug>
#include "objectWindow.h"

extern list<Triangle> face;

class ThreadDraw : public QThread
{
public:
    ThreadDraw();
    QSurfaceFormat format;
    ObjectWindow window;
};

ThreadDraw::ThreadDraw()
{
    format.setSamples(5);
    window.setFormat(format);
    window.show();
    window.setAnimating(true);
}
