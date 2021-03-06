#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "CCBinding.h"
#include "NoteBinding.h"

class Sprite
{
public:
    Sprite() 
    {
        x = 0.0f;
        y = 0.0f;
        w = 0;
        h = 0;
        rot = 0;
        scale = 1.0f;
        res = NULL;
    }

  Sprite(SDL_Texture* resourse)
  {
    x = 0.0f;
    y = 0.0f;
    w = 0;
    h = 0;
    rot = 0;
    scale = 1.0f;
    res = resourse;
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
  void setRes(SDL_Texture* inRes) { res = inRes; };
  std::vector<CCBinding*> c_binding;
  std::vector<NoteBinding*> n_binding;
  //TODO ADD ALPHA SCALING
  ~Sprite() { SDL_DestroyTexture(res); };
private:
  float x;
  float y;
  int w;
  int h;
  int rot;
  float scale;


  
  SDL_Texture* res;
};
