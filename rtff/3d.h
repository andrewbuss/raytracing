#include <math.h>
#pragma once

class Vector{
 public:
  float x;
  float y;
  float z;
  Vector(){x = 0; y = 0; z = 0;} 
  Vector(float _x, float _y, float _z){
    x = _x;
    y = _y;
    z = _z;
  }
  inline void normalize(){
    float nf = 1.0/sqrt(x*x+y*y+z*z);
    x*=nf;
    y*=nf;
    z*=nf;
  }
  inline Vector operator*(float f);
  inline Vector operator/(float f);
  inline Vector operator-(Vector p);
  inline Vector operator+(Vector v);
};

class Ray{
 public:
  Vector o;
  Vector v;
  Vector p;
};

inline Vector CrossProduct(Vector v1, Vector v2){
  return Vector(v1.y*v2.z-v1.z*v2.y,
		v1.z*v2.x-v1.x*v2.z,
		v1.x*v2.y-v1.y*v2.x);
}
inline float DotProduct(Vector v1, Vector v2){
  return (v1.x*v2.x+
	  v1.y*v2.y+
	  v1.z*v2.z);
}
inline float Distance(Vector p1, Vector p2){
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+
	      (p1.y-p2.y)*(p1.y-p2.y)+
	      (p1.z-p2.z)*(p1.z-p2.z));
}
inline Vector Vector::operator-(Vector p){
  return Vector(x-p.x,
		y-p.y,
		z-p.z);
}
inline Vector Vector::operator+(Vector v){
  return Vector(x+v.x,
		y+v.y,
		z+v.z);
}
inline Vector Vector::operator*(float f){
  return Vector(f*x,
		f*y,
		f*z);
}
inline Vector Vector::operator/(float f){
  float nf = 1.0/f;
  return operator*(nf);
}
