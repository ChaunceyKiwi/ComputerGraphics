#ifndef TRI_H
#define TRI_H

#include "vec.h"

class Triangle
{
    private:
        vec4 p1,p2,p3;
    public:
        Triangle(vec4 _p1, vec4 _p2, vec4 _p3){ p1 = _p1;p2 = _p2;p3 = _p3;}
        void getVertice(vec4 &_p1,vec4 &_p2,vec4 &_p3){_p1 = p1;_p2 = p2;_p3 = p3;}
};

#endif // TRI_H
