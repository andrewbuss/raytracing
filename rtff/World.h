#pragma once
#include "3d.h"
#include <limits>
#include <stdio.h>

struct Intersection{
  Vector v;
  Vector n;
  float t;
};

struct Sphere{
  Vector c;
  float r;
};

class World{
 public:
  Sphere* objects;
  int len;
  World(){
    objects = (Sphere*)malloc(sizeof(Sphere)*100*4);
    len = 0;
  }
  void AddSphere(Sphere in){
    objects[len]=in;
    len++;
  }
  Intersection Intersects(Ray r){
    Intersection is;
    is.t = 12345678;
    for(int i=0;i<len;i++){
      Sphere s = objects[i];
      float a = ((r.o.x-r.p.x)*(r.o.x-r.p.x)+
		 (r.o.y-r.p.y)*(r.o.y-r.p.y)+
		 (r.o.z-r.p.z)*(r.o.z-r.p.z));
      float b = 2*((r.p.x-r.o.x)*(r.o.x-s.c.x)+
		   (r.p.y-r.o.y)*(r.o.y-s.c.y)+
		   (r.p.z-r.o.z)*(r.o.z-s.c.z));
      float c = ((r.o.x-s.c.x)*(r.o.x-s.c.x)+
		 (r.o.y-s.c.y)*(r.o.y-s.c.y)+
		 (r.o.z-s.c.z)*(r.o.z-s.c.z))-s.r*s.r;
      float d = b*b-4*a*c;
      if(d<0) continue;
      float t = (-b-sqrt(d))/(2.0*a);
      if(t>0.0 && t<is.t){
	is.v = r.o+r.v*t;
	is.t = t;
	is.n = is.v-s.c;
	is.n.normalize();
      }
      t = (-b+sqrt(d))/(2.0*a);
      if(t>0.0 && t<is.t){
	is.v = r.o+r.v*t;
	is.t = t;
	is.n = is.v-s.c;
	is.n.normalize();
      }
    }
    return is;
  }
};
