#ifndef VEC_H
#define VEC_H

#include <QOpenGLFunctions>
#include <cmath>
#include <cstdio>
#include <iostream>

const GLfloat  DivideByZeroTolerance = GLfloat(1.0e-07);
const GLfloat  DegreesToRadians = M_PI / 180.0;
using namespace std;

struct vec4 {

    GLfloat  x;
    GLfloat  y;
    GLfloat  z;
    GLfloat  w;

    vec4( GLfloat s = GLfloat(0.0) ) :
	x(s), y(s), z(s), w(s) {}

    vec4( GLfloat x, GLfloat y, GLfloat z, GLfloat w ) :
	x(x), y(y), z(z), w(w) {}

    vec4( const vec4& v ) { x = v.x;  y = v.y;  z = v.z;  w = v.w; }

    //
    //  --- Indexing Operator ---
    //

    GLfloat& operator [] ( int i ) { return *(&x + i); }
    const GLfloat operator [] ( int i ) const { return *(&x + i); }

    //
    //  --- (non-modifying) Arithematic Operators ---
    //

    vec4 operator - () const  // unary minus operator
	{ return vec4( -x, -y, -z, -w ); }

    vec4 operator + ( const vec4& v ) const
	{ return vec4( x + v.x, y + v.y, z + v.z, w + v.w ); }

    vec4 operator - ( const vec4& v ) const
	{ return vec4( x - v.x, y - v.y, z - v.z, w - v.w ); }

    vec4 operator * ( const GLfloat s ) const
	{ return vec4( s*x, s*y, s*z, s*w ); }

    vec4 operator * ( const vec4& v ) const
	{ return vec4( x*v.x, y*v.y, z*v.z, w*v.z ); }

    friend vec4 operator * ( const GLfloat s, const vec4& v )
	{ return v * s; }

    vec4 operator / ( const GLfloat s ) const {
	GLfloat r = GLfloat(1.0) / s;
	return *this * r;
    }

    //
    //  --- (modifying) Arithematic Operators ---
    //

    vec4& operator += ( const vec4& v )
	{ x += v.x;  y += v.y;  z += v.z;  w += v.w;  return *this; }

    vec4& operator -= ( const vec4& v )
	{ x -= v.x;  y -= v.y;  z -= v.z;  w -= v.w;  return *this; }

    vec4& operator *= ( const GLfloat s )
	{ x *= s;  y *= s;  z *= s;  w *= s;  return *this; }

    vec4& operator *= ( const vec4& v )
	{ x *= v.x, y *= v.y, z *= v.z, w *= v.w;  return *this; }

    vec4& operator /= ( const GLfloat s ) {
	GLfloat r = GLfloat(1.0) / s;
	*this *= r;
	return *this;
    }
	
    //
    //  --- Insertion and Extraction Operators ---
    //
    friend std::ostream& operator << ( std::ostream& os, const vec4& v ) {
	return os << "( " << v.x << ", " << v.y
		  << ", " << v.z << ", " << v.w << " )";
    }

    friend std::istream& operator >> ( std::istream& is, vec4& v )
	{ return is >> v.x >> v.y >> v.z >> v.w; }

    //
    //  --- Conversion Operators ---
    //
    operator const GLfloat* () const
	{ return static_cast<const GLfloat*>( &x ); }

    operator GLfloat* ()
	{ return static_cast<GLfloat*>( &x ); }
};

inline
GLfloat dot( const vec4& u, const vec4& v ) {
    return u.x*v.x + u.y*v.y + u.z*v.z + u.w+v.w;
}

inline
GLfloat length( const vec4& v ) {
    return std::sqrt( dot(v,v) );
}

inline
vec4 normalize( const vec4& v ) {
    return v / length(v);
}

inline
vec4 cross(const vec4& a, const vec4& b )
{
    return vec4( a.y * b.z - a.z * b.y,
         a.z * b.x - a.x * b.z,
         a.x * b.y - a.y * b.x, 0.0 );
}


#endif // VEC_H
