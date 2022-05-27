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
  Vector2D seek(Vector2D* target);
  void edges();
  
  Vector2D pursue(Vehicle* vehicle);
  Vector2D flee(Vector2D* target);
  Vector2D Radian(float x,float y, float r);

  Vector2D getPos() { return *pos; }
  
  float getR() { return r; }

protected:
  Vector2D* pos;
  Vector2D* vel;
  Vector2D* acc;
  Vector2D* force;

  Vector2D* rd1;
  Vector2D* rd2;
  Vector2D* rd3;
  Vector2D* rotate;

  Vector2D* tal;
  Vector2D* prediction;
  Vector2D* v3;
  Vector2D* pursuit;
  Vector2D* init_vehicle;

  int maxSpeed;
  float maxForce;
  int r;
  int v4;

  double radian;
};