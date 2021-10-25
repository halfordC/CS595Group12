#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sprite
{
public:
  Sprite()
  {
    x = 0.0f;
    y = 0.0f;
    w = 0;
    h = 0;
    res = NULL;
  }
  Sprite(float xPos, float yPos, int width, int height, SDL_Texture* resource)
  {
    x = xPos;
    y = yPos;
    w = width;
    h = height;
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
  int getWidth() { return w; };
  int getHeight() { return h; };
  int getRotation() { return rot; };
  float getScale() { return scale; };
  SDL_Texture* getRes() { return res; };
private:
  float x;
  float y;
  int w;
  int h;
  int rot;
  float scale;
  SDL_Texture* res;
};
