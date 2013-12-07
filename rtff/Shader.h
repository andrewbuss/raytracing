#include "3d.h"
#include "World.h"
#include "Color.h"

struct Light{
  Vector v;
  Color c;
};
class Shader{
 public:
  Light* lights;
  int len;
  void AddLight(Vector v, Color c){
    Light light;
    light.v = v;
    light.c = c;
    lights[len++] = light;
  }    
  Shader(){
    lights = (Light*) malloc(sizeof(Light)*100);
    len = 0;    
  }
  Color Shade(Intersection is){
    if(is.t>10000) return Color(0,0,0);
    Color color(0,0,0);
    for(int i = 0; i<len; i++){
      Vector dv = lights[i].v-is.v;
      dv.normalize();
      float cosine = DotProduct(dv,is.n);
      if(cosine<0) continue;
      color += lights[i].c*cosine;
    }
    return color;
  }
};
      
