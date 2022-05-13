#include "Walker.h"
#include "InputHandler.h"

Walker::Walker() 
{
  Dir = new Vector2D(0,0);
  m_vehicle = new Vehicle(100,100);
}

void Walker::update() 
{
  m_vehicle->seek(Dir);
  m_vehicle->update();
  Dir = TheInputHandler::Instance()->getMousePosition();
}

void Walker::draw(SDL_Renderer* renderer)
{
 filledCircleRGBA(renderer, Dir->getX(), Dir->getY(), 15, 255, 255,0,200); 
m_vehicle->draw(renderer);
}
