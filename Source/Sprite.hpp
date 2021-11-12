#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Sprite
{
public:
  Sprite()
  {
    x = 0.0f;
    y = 0.0f;
    w = 0;
    h = 0;
    xV = 1.0f;
    yV = 1.0f;
    res = NULL;
  }
  Sprite(float xPos, float yPos, int width, int height, SDL_Texture* resource, int r1)
  {
    x = xPos;
    y = yPos;
    w = width;
    h = height;
    xV = (r1 == 0) ? 1.0f : -1.0f;
    yV = (r1 == 0) ? 1.0f : -1.0f;
    rot = 0;
    scale = 1.0f;
    res = resource;
  };
  void setX(float xPos) { x = xPos; };
  void setY(float yPos) { y = yPos; };
  void setWidth(int width) { if( width > 0) { w = width; } };
  void setHeight(int height) { if( height > 0 ) { h = height; } };
  void setRotation(int rotation) { rot = rotation; };
  void setScale(float s){ if(s > 0) { scale = s; } };
  float getX() { return x; };
  float getY() { return y; };
  void update() 
  { 
      
      y += (0.01f * yV);
      x += (0.01f * xV);
      rot += 10;
      if (y + (0.01f * yV) >= 1.0f) yV = -1;
      if (y + (0.01f * yV) < 0.0f) yV = 1;
      if (x + (0.01f * xV) >= 1.0f) xV = -1;
      if (x + (0.01f * xV) < 0.0f) xV = 1;
  };
  int getWidth() { return w; };
  int getHeight() { return h; };
  int getRotation() { return rot; };
  float getScale() { return scale; };
  SDL_Texture* getRes() { return res; };
  //TODO ADD ALPHA SCALING
  ~Sprite() { SDL_DestroyTexture(res); };
private:
  float x;
  float y;
  int w;
  int h;
  float xV;
  float yV;
  int rot;
  float scale;
  SDL_Texture* res;
};
