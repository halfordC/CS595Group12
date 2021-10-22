#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sprite
{
public:
  Sprite(float xPos, float yPos, float width, float height, SDL_Texture* resource)
  {
    x = xPos;
    y = yPos;
    w = width;
    h = height;
    scale = 1.0f;
    res = resource;
  };
  void setX(float xPos) { x = xPos; };
  void setY(float yPos) { y = yPos; };
  void setWidth(float width) { if( width > 0) { w = width; } };
  void setHeight(float height) { if( height > 0 ) { h = height; } };
  void setScale(float s){ if(s > 0) { scale = s; } };
  float getX() { return x; };
  float getY() { return y; };
  float getWidth() { return w; };
  float getHeight() { return h; };
  float getScale() { return scale; };
private:
  float x;
  float y;
  float w;
  float h;
  float scale;
  SDL_Texture* res;
};
