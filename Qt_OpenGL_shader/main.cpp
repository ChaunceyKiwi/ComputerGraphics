#include <QApplication>
#include "ObjectWindow.h"
#include "videoplayer.h"
#include "threadGetTriangle.h"
#include "threadDraw.h"
#include "videothread.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "triangle.h"
using namespace std;

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

    vec4 p1 = vec4(1.0,2.0,3.0,1.0);
    vec4 p2 = vec4(3.0,2.0,1.0,1.0);
    vec4 p3 = vec4(2.0,3.0,3.0,1.0);
    Triangle a1(p1,p2,p3);
    Triangle a2(p3,p1,p2);

    list<Triangle> triList;
    std::list<Triangle>::iterator tri;

    triList.push_back(a1);
    triList.push_back(a2);

    for (tri=triList.begin(); tri!=triList.end(); tri++)
        tri->showData();

    ThreadDraw threadDraw; //thread to draw object
    threadDraw.start();

//    MediaThread mediaThread;
//    mediaThread.start();
//    QGraphicsScene scene;
//    QGraphicsView view(&scene);
//    QGraphicsPixmapItem item(QPixmap("/Users/KiwiDc/Desktop/nice.png"));
//    scene.addItem(&item);
//    view.show();

    return app.exec();
}
