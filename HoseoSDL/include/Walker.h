#pragma once

#include "main.h"
#include "Vector2D.h"
#include "Vehicle.h"

class Walker 
{
  
public:
  Walker();
  void draw(SDL_Renderer* renderer);
  void update();

private:
  Vector2D* Dir;
  Vehicle* m_vehicle;
};