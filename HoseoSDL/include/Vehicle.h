#pragma once

#include "main.h"

#include "Vector2D.h"

class Vehicle 
{
  
public:
  Vehicle(int x, int y);
  void draw(SDL_Renderer* renderer);
  void update();
  void applyForce(Vector2D* f);
  void seek(Vector2D* target);
  void edges();
  Vector2D Radian(float x,float y, float r);

private:
  Vector2D* pos;
  Vector2D* vel;
  Vector2D* acc;
  Vector2D* force;
  Vector2D* rd1;
  Vector2D* rd2;
  Vector2D* rd3;
  Vector2D* rotate;

  int maxSpeed;
  float maxForce;
  int r;

  double radian;
};