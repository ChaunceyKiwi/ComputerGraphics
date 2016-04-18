#include <QtCore>
#include <QDebug>
#include <iostream>
#include <string>
#include <fstream>
#include "triangle.h"
#include "vertex.h"


void divideStringBySpace(char* origin,char derivative[4][10]);
extern list<Triangle> face;
extern list<Vertex> pointsDataList;
extern list<Vertex> linesDataList;

class ThreadGetData : public QThread
{
public:
    ThreadGetData();
    void inputFaces(list<Triangle> triList);
    void inputLines(list<Vertex> pointList);
    void inputPoints(list<Vertex> pointList);
    void inputFromSMF(string address);
};

ThreadGetData::ThreadGetData(){
}

// Input data of faces
void ThreadGetData::inputFaces(list<Triangle> triList){

    list<Triangle>::iterator tri;

    for (tri = triList.begin(); tri != triList.end(); tri++){
            face.push_back(*tri);
    }
}

// Input data of lines
void ThreadGetData::inputLines(list<Vertex> pointList){
    list<Vertex>::iterator point;

    for(point = pointList.begin(); point != pointList.end(); point++){
        linesDataList.push_back(*point);
    }
}

// Input data of points
void ThreadGetData::inputPoints(list<Vertex> pointList){
    list<Vertex>::iterator point;

    for(point = pointList.begin(); point != pointList.end(); point++){
        pointsDataList.push_back(*point);
    }
}

// Input data from .smf file
void ThreadGetData::inputFromSMF(string address){
       string line;
       char line_[90];
       char lineSplit[4][10];
       float vert[15000][3];

       ifstream input(address.c_str());
       getline(input,line);
       strcpy(line_, line.c_str());
       divideStringBySpace(line_, lineSplit);
       int numOfVert = atoi(lineSplit[1]);
       int numOfFace = atoi(lineSplit[2]);

       // get vertices
       for (int i = 0;i < numOfVert;i++){
           getline(input,line);
           strcpy(line_, line.c_str());
           divideStringBySpace(line_, lineSplit);
           vert[i][0] = atof(lineSplit[1]);
           vert[i][1] = atof(lineSplit[2]);
           vert[i][2] = atof(lineSplit[3]);
       }

       // get all faces
       for (int i = 0;i < numOfFace;i++){
           getline(input,line);
           strcpy(line_, line.c_str());
           divideStringBySpace(line_, lineSplit);
           int index0 = atoi(lineSplit[1]) - 1;
           int index1 = atoi(lineSplit[2]) - 1;
           int index2 = atoi(lineSplit[3]) - 1;

           vec4 p1 = vec4(vert[index0][0],vert[index0][1],vert[index0][2],1.0);
           vec4 p2 = vec4(vert[index1][0],vert[index1][1],vert[index1][2],1.0);
           vec4 p3 = vec4(vert[index2][0],vert[index2][1],vert[index2][2],1.0);
           Triangle curr = Triangle(p1,p2,p3);
           face.push_back(curr);
       }
}

// Function to handle with strings
void divideStringBySpace(char* origin,char derivative[4][10]){
    int i = 0,j = 0,k = 0;

    while(origin[i] != '\r' && origin[i] != '\n' && origin[i] != '\0'){
        while(origin[i]!=' ' && origin[i] != '\r' && origin[i] != '\n' && origin[i] != '\0')
        {
            derivative[j][k] = origin[i];
            k++;
            i++;
        }
        if(origin[i] == '\r' || origin[i] == '\n' || origin[i] == '\0') break;
        derivative[j][k] = '\0';
        k = 0;
        j++;
        i++;
    }
    derivative[j][k] = '\0';
    derivative[j][k+1] = '\0';
}
