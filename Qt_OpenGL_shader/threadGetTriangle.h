#include <QtCore>
#include <QDebug>
#include "getData.h"

extern int numOfVert;
extern int numOfFace;
extern float vert[15000][3];
extern int face[30000][3];
int num = 1;

class ThreadGetTriangle : public QThread
{
public:
    ThreadGetTriangle();
    void run();
};

ThreadGetTriangle::ThreadGetTriangle(){

}

void ThreadGetTriangle::run(){
    while(1){
        sleep(1);
        getTriangles(vert,face,numOfVert,numOfFace,num);
        num += 1000;
    }
}
