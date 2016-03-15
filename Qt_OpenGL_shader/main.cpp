#include <QApplication>
#include "ObjectWindow.h"
#include "videoplayer.h"
#include "threadGetTriangle.h"
#include "threadDraw.h"
#include "videothread.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

int numOfVert;
int numOfFace;
float vert[15000][3];
int face[30000][3];

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ThreadGetTriangle threadGetTriangle; //thread to get data
    threadGetTriangle.start();
    //threadGetTriangle.input(vector<Triangle>& vec_tri);

    ThreadDraw threadDraw; //thread to draw object
    threadDraw.start();

    MediaThread mediaThread;
    mediaThread.start();
//    QGraphicsScene scene;
//    QGraphicsView view(&scene);
//    QGraphicsPixmapItem item(QPixmap("/Users/KiwiDc/Desktop/nice.png"));
//    scene.addItem(&item);
//    view.show();

    return app.exec();
}
