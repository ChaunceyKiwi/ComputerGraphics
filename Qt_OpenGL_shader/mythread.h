#include <QtCore>
#include <QDebug>
#include "getData.h"

extern int numOfVert;
extern int numOfFace;
extern float vert[15000][3];
extern int face[30000][3];
int num = 1;


class MyThread : public QThread
{
public:
    MyThread();
    QSurfaceFormat format;
    ObjectWindow window;

    void run();
    QString name;
};

MyThread::MyThread()
{
    format.setSamples(5);
    window.setFormat(format);
    window.show();
    window.setAnimating(true);
}

void MyThread::run()
{
    while(1){
        sleep(1);
        getTriangles(vert,face,numOfVert,numOfFace,num);
        num += 1000;
//        cout<<"!!"<<num<<endl;
    }
}
