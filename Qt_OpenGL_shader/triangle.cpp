#include "triangle.h"
using namespace std;

Triangle::Triangle(vec4 _p1, vec4 _p2, vec4 _p3){
    p1 = _p1;
    p2 = _p2;
    p3 = _p3;
}

void Triangle::showData(){
    cout<<p1<<endl;
    cout<<p2<<endl;
    cout<<p3<<endl;
}
