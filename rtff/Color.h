#pragma once

class Color{
 public:
  float r;
  float g;
  float b;
  Color(float _r, float _g, float _b){
    r=_r;
    g=_g;
    b=_b;
  }
  Color(){
    r=0;
    g=0;
    b=0;
  }
  Color operator*(float f){
    return Color(r*f,g*f,b*f);
  }
  void operator+=(Color c){
    r+=c.r;
    g+=c.g;
    b+=c.b;
  }
};
