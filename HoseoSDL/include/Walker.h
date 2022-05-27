#pragma once

#include "main.h"
#include "Vector2D.h"
#include "Vehicle.h"
#include "Target.h"


class Walker 
{
  
public:
  Walker();
  void draw(SDL_Renderer* renderer);
  void update();
  

private:
  Vehicle* pursuer;
  Target* target;

  Vector2D* d;
  Vector2D* steering;

  
  bool pause;
};