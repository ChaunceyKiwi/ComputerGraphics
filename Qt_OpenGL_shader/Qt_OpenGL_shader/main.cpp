#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "threadGetTriangle.h"
#include "threadDraw.h"

list<Triangle> face;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ThreadGetTriangle threadGetTriangle; //thread to get data
    threadGetTriangle.start();
    threadGetTriangle.inputFromSMF("/Users/KiwiDc/Desktop/exp/man.smf");

//    vec4 p1 = vec4(-0.5, 0.0, 0.0, 1.0);
//    vec4 p2 = vec4(0.5, 0.0, 0.0, 1.0);
//    vec4 p3 = vec4(0.0, 1.0, 0.0, 1.0);
//    vec4 p4 = vec4(-0.5, 0.0, 0.0, 1.0);
//    list<Triangle> triList;
//    Triangle a1(p1,p2,p3);
//    Triangle a2(p1,p2,p4);
//    triList.push_back(a1);
//    triList.push_back(a2);
//    threadGetTriangle.input(triList);

    ThreadDraw threadDraw; //thread to draw object
    threadDraw.start();

    return app.exec();
}
