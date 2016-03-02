//#include <iostream>
//#include <fstream>
//#include <string>
//#include <string.h>
//#include <sstream>
//#include <vector>
//#include <map>
//#define numOfVertMax 30000
//#define numOfFaceMax 60000
//using namespace std;
//typedef pair<int, int> key_type;
//map<key_type,int> flag;
//map<key_type,int> indexOfVert;
//using namespace std;

//class W_edge;
//class Vertex;
//class Face;

//int edgeCount;

//class W_edge
//{
//public:
//    Vertex *start, *end;
//    Face  *left, *right;
//    W_edge *left_prev, *left_next;
//    W_edge *right_prev, *right_next;
//};

//class Vertex
//{
//public:
//    int index;
//    float x, y, z;
//    W_edge *edge;
    
//    void setValue(int index_,float x_,float y_,float z_){index = index_;x = x_;y = y_; z = z_;}
//};

//class Face{
//public:
//    W_edge *edge;
//};

//void divideStringBySpace(char* origin,char derivative[4][10]);
//void updateIndexOfVert(int index1,int index2);
//int getIndexOfVert(int index1,int index2);
//int checkState(int index1,int index2);
//void indexAdd(int index1,int index2);
//void insertEdge(int indexOfFace,int v1,int v2,Vertex* vertex,Face* face,W_edge *newEdge,W_edge *newEdge1,W_edge *newEdge2);
//void getVertexFromFace(Face* face ,Vertex* vertex);
//void getMesh(string address,Vertex* vertex,Face* face,W_edge edge[numOfVertMax+numOfFaceMax-1],int& numOfVert,int& numOfFace,int& numOfEdge);
//void export2SMF(Vertex* vertex,Face* faceAll,int& numOfVert,int& numOfFace);

//void divideStringBySpace(char* origin,char derivative[4][10]){
//    int i = 0,j = 0,k = 0;
    
//    while(origin[i] != '\r' && origin[i] != '\n' && origin[i] != '\0'){
//        while(origin[i]!=' ' && origin[i] != '\r' && origin[i] != '\n' && origin[i] != '\0')
//        {
//            derivative[j][k] = origin[i];
//            k++;
//            i++;
//        }
//        if(origin[i] == '\r' || origin[i] == '\n' || origin[i] == '\0') break;
//        derivative[j][k] = '\0';
//        k = 0;
//        j++;
//        i++;
//    }
//    derivative[j][k] = '\0';
//    derivative[j][k+1] = '\0';
//}

//void updateIndexOfVert(int index1,int index2){
//    if(index1 >= index2)
//        indexOfVert[key_type(index2,index1)] = edgeCount;
//    else
//        indexOfVert[key_type(index1,index2)] = edgeCount;
//}

//int getIndexOfVert(int index1,int index2){
//    if(index1 >= index2)
//        return indexOfVert[key_type(index2,index1)];
//    else
//        return indexOfVert[key_type(index1,index2)];
//}

//int checkState(int index1,int index2){
//    if(index1 >= index2)
//        return flag[key_type(index2,index1)];
//    else
//        return flag[key_type(index1,index2)];
//}

//void indexAdd(int index1,int index2){
    
//    if(index1 >= index2)
//        flag[key_type(index2,index1)]++;
//    else
//        flag[key_type(index1,index2)]++;
//}

//void insertEdge(int indexOfFace,int v1,int v2,Vertex* vertex,Face* face,W_edge *newEdge,W_edge *newEdge1,W_edge *newEdge2){
    
//    int state = checkState(v1,v2);
    
//    if(state == 0){
//        newEdge->start = &vertex[v1];
//        newEdge->end   = &vertex[v2];
//        newEdge->right = &face[indexOfFace];
//        newEdge->right_next = newEdge1;
//        newEdge->right_prev = newEdge2;
//        indexAdd(v1, v2);
//    }else if (state == 1){
//        newEdge->left = &face[indexOfFace];
//        newEdge->left_next = newEdge2;
//        newEdge->left_prev = newEdge1;
//        indexAdd(v1, v2);
//    }else{
//        cout<<"Error!"<<endl;
//    }
    
//    face[indexOfFace].edge = newEdge;
//    vertex[v1].edge = newEdge;
//    vertex[v2].edge = newEdge;
//}

//void getVertexFromFace(Face* face ,Vertex* vertex){
    
//    if(face->edge->right == face){
//        vertex[0] = *(face->edge->start);
//        vertex[1] = *(face->edge->end);
//        if(face->edge->end != face->edge->right_next->end )
//            vertex[2] = *(face->edge->right_next->end);
//        else
//            vertex[2] = *(face->edge->right_next->start);
//    }else{
//        vertex[0] = *(face->edge->start);
//        vertex[1] = *(face->edge->end);
//        if(face->edge->end != face->edge->left_next->end )
//            vertex[2] = *(face->edge->left_next->end);
//        else
//            vertex[2] = *(face->edge->left_next->start);
//    }
//}

//void getMesh(string address,Vertex* vertex,Face* face,W_edge edge[numOfVertMax+numOfFaceMax-1],int& numOfVert,int& numOfFace,int& numOfEdge) {
//    string line;
//    char line_[90];
//    char lineSplit[4][10];
    
//    vector<string> v;
//    edgeCount = 1;
    
//    ifstream input(address);
//    getline(input,line);
//    strcpy(line_, line.c_str());
    
//    divideStringBySpace(line_, lineSplit);
    
    
//    numOfVert = stoi(lineSplit[1]);
//    numOfFace = stoi(lineSplit[2]);
    
    
//    for (int i = 0;i < numOfVert;i++){
//        getline(input,line);
//        strcpy(line_, line.c_str());
//        divideStringBySpace(line_, lineSplit);
//        vertex[i+1].setValue(i+1,stof(lineSplit[1]), stof(lineSplit[2]), stof(lineSplit[3]));
//    }
    
    
//    for(int i = 0; i < numOfFace;i++){
//        getline(input,line);
//        strcpy(line_, line.c_str());
//        divideStringBySpace(line_, lineSplit);
//        W_edge *newEdge0,*newEdge1,*newEdge2;
        
//        int ind1 = stoi(lineSplit[1]);
//        int ind2 = stoi(lineSplit[2]);
//        int ind3 = stoi(lineSplit[3]);
        
//        int state1 = getIndexOfVert(ind1,ind3);
//        int state2 = getIndexOfVert(ind3,ind2);
//        int state3 = getIndexOfVert(ind2,ind1);
        
//        if(state1 == 0){
//            updateIndexOfVert(ind1,ind3);
//            newEdge0 = &edge[edgeCount++];
//        }else
//            newEdge0 = &edge[state1];
        
//        if(state2 == 0){
//            updateIndexOfVert(ind3,ind2);
//            newEdge1 = &edge[edgeCount++];
//        }else
//            newEdge1 = &edge[state2];
        
//        if(state3 == 0){
//            updateIndexOfVert(ind2,ind1);
//            newEdge2 = &edge[edgeCount++];
//        }else
//            newEdge2 = &edge[state3];
        
        
//        insertEdge(i+1, ind1, ind3, vertex, face, newEdge0,newEdge1,newEdge2);
//        insertEdge(i+1, ind3, ind2, vertex, face, newEdge1,newEdge2,newEdge0);
//        insertEdge(i+1, ind2, ind1, vertex, face, newEdge2,newEdge0,newEdge1);
//    }
    
//    numOfEdge = edgeCount - 1;
    
//}

//void export2SMF(Vertex* vertex,Face* faceAll,int& numOfVert,int& numOfFace)
//{
//    int i;
//    FILE *pFile;
//    pFile = fopen("output.smf","w");
//    if(pFile != NULL){
//        fprintf(pFile, "# %d %d\n",numOfVert,numOfFace);
        
//        for(i = 0;i < numOfVert;i++){
//            fprintf(pFile, "v %f %f %f\n",vertex[i+1].x,vertex[i+1].y,vertex[i+1].z);
//        }
        
//        for(i = 0;i < numOfFace;i++){
//            Face* face = &faceAll[i+1];
//            if(face->edge->right == face){
//                if(face->edge->end != face->edge->right_next->end )
//                    fprintf(pFile, "f %d %d %d\n",face->edge->start->index,face->edge->end->index,face->edge->right_next->end->index);
//                else
//                    fprintf(pFile, "f %d %d %d\n",face->edge->start->index,face->edge->end->index,face->edge->right_next->start->index);
//            }else{
//                if(face->edge->end != face->edge->left_next->end )
//                    fprintf(pFile, "f %d %d %d\n",face->edge->start->index,face->edge->end->index,face->edge->left_next->end->index);
//                else
//                    fprintf(pFile, "f %d %d %d\n",face->edge->start->index,face->edge->end->index,face->edge->left_next->start->index);
//            }
//        }
        
        
//        fclose(pFile);
//    }
//    cout<<"Export SMF file done!"<<endl;
//}
