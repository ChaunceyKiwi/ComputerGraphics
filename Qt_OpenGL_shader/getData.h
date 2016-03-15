#include <iostream>
#include <string>
#include <fstream>

using namespace std;

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

void getTriangles(float vert[15000][3],int face[30000][3], int &numOfVert, int &numOfFace, int num)
{
    string line;
    char line_[90];
    char lineSplit[4][10];

    ifstream input("/Users/KiwiDc/Desktop/exp/man.smf");
    getline(input,line);
    strcpy(line_, line.c_str());
    divideStringBySpace(line_, lineSplit);
    numOfVert = atoi(lineSplit[1]);
    numOfFace = atoi(lineSplit[2]);

    for (int i = 0;i < numOfVert;i++){
        getline(input,line);
        strcpy(line_, line.c_str());
        divideStringBySpace(line_, lineSplit);
        vert[i][0] = atof(lineSplit[1]);
        vert[i][1] = atof(lineSplit[2]);
        vert[i][2] = atof(lineSplit[3]);
    }

    for (int i = 0;i < num;i++){
        getline(input,line);
        strcpy(line_, line.c_str());
        divideStringBySpace(line_, lineSplit);
        face[i][0] = atoi(lineSplit[1]);
        face[i][1] = atoi(lineSplit[2]);
        face[i][2] = atoi(lineSplit[3]);
    }
}
