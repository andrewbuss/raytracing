#include <SDL/SDL.h>
#include <math.h>

#include "3d.h"
#include "Color.h"
#include "World.h"
#include "Shader.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define XRES 1000
#define YRES 800

float getoffset(){
  static int state;
  state++;
  switch(state%18){
  case 1:
    return 0.25;
  case 2:
    return 0.25;
  case 3:
    return 0.5;
  case 4:
    return 0.25;
  case 5:
    return 0.75;
  case 6:
    return 0.25;
  case 7:
    return 0.25;
  case 8:
    return 0.5;
  case 9:
    return 0.5;
  case 10:
    return 0.5;
  case 11:
    return 0.75;
  case 12:
    return 0.5;
  case 13:
    return 0.25;
  case 14:
    return 0.75;
  case 15:
    return 0.5;
  case 16:
    return 0.75;
  case 17:
    return 0.75;
  case 0:
    return 0.75;
  }
}
    
  
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel){
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}
int main(){
  World world;
  Shader shader;
  shader.AddLight(Vector(-10,2,-5), Color(1.0,1.0,1.0));
  shader.AddLight(Vector(5,10,-5), Color(1.0,1.0,1.0));
  Sphere sphere;
  sphere.c.x = 0;
  sphere.c.y = 0;
  sphere.c.z = -5;
  sphere.r = 1;
  world.AddSphere(sphere);
  Sphere sphere2;
  sphere2.c.x = 3;
  sphere2.c.y = 3;
  sphere2.c.z = -10;
  sphere2.r = 2;
  world.AddSphere(sphere2);
  Vector camera(-4,4,0);
  Vector vp_mid(-3,3,-1);
  Vector camera_up(0,1,0);
  Vector camera_right = CrossProduct(vp_mid-camera,camera_up);
  float hfov = M_PI*130.0/360.0;
  float vfov = ((float)YRES)/((float)XRES)*hfov;
  camera_up = CrossProduct(camera_right,vp_mid-camera);
  camera_right.normalize();
  camera_up.normalize();
  printf("Camera position: (%f, %f, %f)\n",camera.x,camera.y,camera.z);
  printf("Viewplane mid: (%f, %f, %f)\n",vp_mid.x,vp_mid.y,vp_mid.z);
  printf("Camera up: (%f, %f, %f)\n",camera_up.x,camera_up.y,camera_up.z);
  printf("Camera right: (%f, %f, %f)\n",camera_right.x,camera_right.y,camera_right.z);
  printf("HFOV: %f, tangent of HFOV: %f\n",hfov,tan(hfov));
  printf("VFOV: %f, tangent of VFOV: %f\n",vfov,tan(vfov));
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface* screen = SDL_SetVideoMode(XRES,YRES, 32, SDL_HWSURFACE);
  Color* buffer = (Color*)malloc(sizeof(Color)*XRES*YRES);
  for(int v=0;v<YRES;v++){
    for(int u=0;u<XRES;u++){
      Color result;
      for(int i=0;i<9;i++){
	Vector vp = vp_mid+
	  camera_up*(XRES/2-v+getoffset())/XRES*Distance(camera,vp_mid)+
	  camera_right*((u-XRES/2+getoffset())/XRES*Distance(camera,vp_mid));
	Ray vr; 
	vr.o = camera;
	vr.v = vp-camera;
	vr.v.normalize();
	vr.p = vr.o+vr.v;
	result = shader.Shade(world.Intersects(vr));
	buffer[XRES*v+u] += result;
      }
      putpixel(screen, u, v, SDL_MapRGB(screen->format, 255*MIN(result.r,1), 255*MIN(result.g,1), 255*MIN(result.b,1)));
    }
    SDL_UpdateRect(screen, 0, v, XRES, 1);
  }
  float max = 1.0;
  for(int i=0;i<XRES*YRES;i++){
    max = MAX(max,buffer[i].r);
    max = MAX(max,buffer[i].g);
    max = MAX(max,buffer[i].b);
  }    
  float nf = 1.0/max;
  for(int i=0;i<XRES*YRES;i++){
    buffer[i].r*=nf;
    buffer[i].g*=nf;
    buffer[i].b*=nf;
  }
  for(int v=0;v<YRES;v++){
    for(int u=0;u<XRES;u++){
      putpixel(screen, u, v, SDL_MapRGB(screen->format, buffer[v*XRES+u].r*255, buffer[v*XRES+u].g*255, buffer[v*XRES+u].b*255));
    }
    SDL_UpdateRect(screen, 0, v, XRES, 1);
  }
  SDL_Event event;
  while(true){
    if(SDL_PollEvent(&event) && event.type == SDL_KEYDOWN){
      printf("Key event!\n");
      return 0;
    }
  }
}

  
