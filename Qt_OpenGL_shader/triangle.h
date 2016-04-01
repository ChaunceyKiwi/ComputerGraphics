#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "include/Angel.h"

class Triangle
{
    private:
        vec4 p1,p2,p3;
    public:
        Triangle(vec4 _p1, vec4 _p2, vec4 _p3);
        void showData();
};


#endif // TRIANGLE_H
