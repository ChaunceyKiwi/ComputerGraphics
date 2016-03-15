#include <QtCore>
#include <QDebug>

extern int numOfVert;
extern int numOfFace;
extern float vert[15000][3];
extern int face[30000][3];

class ThreadDraw : public QThread
{
public:
    ThreadDraw();
    QSurfaceFormat format;
    ObjectWindow window;

    void run();
    QString name;
};

ThreadDraw::ThreadDraw()
{
    format.setSamples(5);
    window.setFormat(format);
    window.show();
    window.setAnimating(true);
}

void ThreadDraw::run()
{

}
