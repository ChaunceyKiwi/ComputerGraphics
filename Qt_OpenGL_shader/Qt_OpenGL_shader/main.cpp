#include <QGuiApplication>
#include "window.h"
#include "threadGetData.h"
#include "threaddraw.h"

list<Triangle> face;
list<Vertex> pointsDataList;
list<Vertex> linesDataList;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ThreadGetData threadGetData; //thread to get data
    threadGetData.start();
    threadGetData.inputFromSMF("/Users/KiwiDc/Desktop/exp/man.smf");

    /* faces import */
//    vec4 p1 = vec4(-0.5, 0.0, 0.0, 1.0);
//    vec4 p2 = vec4(0.5, 0.0, 0.0, 1.0);
//    vec4 p3 = vec4(0.0, 1.0, 0.0, 1.0);
//    vec4 p4 = vec4(-0.5, 0.0, 0.0, 1.0);
//    list<Triangle> triList;
//    Triangle a1(p1,p2,p3);
//    Triangle a2(p1,p2,p4);
//    triList.push_back(a1);
//    triList.push_back(a2);
//    threadGetData.inputFaces(triList);

    /*points import*/
    Vertex point1 = Vertex( QVector3D( 0.50f, 0.50f, 0.00f), QVector3D(1.0f, 0.0f, 0.0f));
    Vertex point2 = Vertex( QVector3D( 0.00f, 0.50f, 0.00f), QVector3D(0.0f, 1.0f, 0.0f));
    Vertex point3 = Vertex( QVector3D( 0.50f, 0.00f, 0.00f), QVector3D(1.0f, 0.0f, 0.0f));

    list<Vertex> pointsListTemp;
    pointsListTemp.push_back(point1);
    pointsListTemp.push_back(point2);
    pointsListTemp.push_back(point3);

    threadGetData.inputPoints(pointsListTemp);

    /*lines import*/
    Vertex l1 = Vertex( QVector3D( 0.00f, 0.00f, 0.00f), QVector3D(0.0f, 0.0f, 0.0f) );
    Vertex l2 = Vertex( QVector3D( 0.50f, 0.70f, 0.50f), QVector3D(0.0f, 0.0f, 0.0f) );
    Vertex l3 = Vertex( QVector3D( 0.50f, 0.70f, -0.50f), QVector3D(0.0f, 0.0f, 0.0f) );
    Vertex l4 = Vertex( QVector3D( 0.00f, 0.00f, 0.00f), QVector3D(0.0f, 0.0f, 0.0f) );
    list<Vertex> linesListTemp;
    linesListTemp.push_back(l1);
    linesListTemp.push_back(l2);
    linesListTemp.push_back(l3);
    linesListTemp.push_back(l4);
    threadGetData.inputLines(linesListTemp);

    ThreadDraw threadDraw; //thread to draw object
    threadDraw.start();

    return app.exec();
}
