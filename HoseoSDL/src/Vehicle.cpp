#define WIDTH (600)
#define HEIGHT (400)

#include "Vehicle.h"
#include <math.h>

Vehicle::Vehicle(int x, int y) : maxSpeed(4), maxForce(0.25f), r(16), v4(0)
{
  pos = new Vector2D(x,y);
  vel = new Vector2D(0,0);
  acc = new Vector2D(0,0);
  force = new Vector2D(0,0);

  rd1 = new Vector2D(1,1);
  rd2 = new Vector2D(1,1);
  rd3 = new Vector2D(1,1);
  rotate = new Vector2D(0,0);

  tal = new Vector2D(0, 0);
  prediction = new Vector2D(0, 0);
  v3 = new Vector2D(0, 0);
  pursuit = new Vector2D(0, 0);
  init_vehicle = new Vector2D(0, 0);
}

void Vehicle::update() 
{
  *vel += *acc;
  vel->limit(maxSpeed);
  *pos += *vel;
  *acc *= 0; 
  
  radian = atan2(vel->getY(), vel->getX());
  
  *rd1 = Radian(-r, -r/2, radian);
  *rd2 = Radian(-r, r/2, radian);
  *rd3 = Radian(r, 0, radian);
  
  edges();
}

void Vehicle::draw(SDL_Renderer* renderer)
{
  
 filledTrigonRGBA(renderer, 
   rd1->getX() + pos->getX() , rd1->getY() + pos->getY() ,
   rd2->getX() + pos->getX() , rd2->getY() + pos->getY() ,
   rd3->getX() + pos->getX() , rd3->getY() + pos->getY() , 
   255, 255, 255, 255);

 
 lineRGBA(renderer, init_vehicle->getX(), init_vehicle->getY(), tal->getX(), tal->getY(), 200, 0, 0, 150);
 filledCircleRGBA(renderer, tal->getX(), tal->getY(), r, 200, 0, 0, 150);
}

Vector2D Vehicle::Radian(float x ,float y, float radian)
{ 
  rotate = new Vector2D(0,0);
  
  rotate->setX(cos(radian) * x - sin(radian) * y);
  rotate->setY(sin(radian) * x + cos(radian) * y);

  return *rotate;
}

void Vehicle::applyForce(Vector2D* f)
{
  *acc += *f;
}

Vector2D Vehicle::flee(Vector2D* target)
{
    return seek(target) * -1;
}

Vector2D Vehicle::seek(Vector2D* target)
{
  *force = *target - *pos;
  force->normalize();
  *force *= maxSpeed;
  *force -= *vel;
  force->limit(maxForce);
 
  return *force;
}


Vector2D Vehicle::pursue(Vehicle* vehicle)
{
    *init_vehicle = *vehicle->pos;

    *tal = *vehicle->pos;
    *prediction = *vehicle->vel;

    *v3 = *tal - *pos;
    float a = v3->length();
    *prediction *= a / 30;

    *tal += *prediction;

    return seek(tal);
}



void Vehicle::edges()
{
  if(pos->getX() > WIDTH + r)
  {
    pos->setX(r);
  }else if(pos->getX() < -r)
  {
    pos->setX(WIDTH + r);
  }
  if(pos->getY() > HEIGHT + r)
  {
    pos->setY(-r);
  }else if(pos->getY() < -r)
  {
    pos->setY(HEIGHT + r);
  }
}