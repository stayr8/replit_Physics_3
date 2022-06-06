#define WIDTH (600)
#define HEIGHT (400)

#include "Walker.h"
#include "InputHandler.h"
#include <random>

Walker::Walker()
{
	Dir = new Vector2D(0, 0);
	steering = new Vector2D(0, 0);
	m_vehicle = new Vehicle(100, 100);
	m_St = new SteeringBehavior(200, 200);
	Force = new Vector2D(0, 0);
	
	m_BG.push_back(new BaseGameEntity(300, 300, 32));
	
}

void Walker::update()
{
	*steering = m_vehicle->arrive(Dir);
	m_vehicle->applyForce(steering);
	m_vehicle->update();

	m_BG[0]->update();

	
	*Force = m_St->Hide(m_vehicle, m_BG);
	m_St->applyForce(Force);
	m_St->update();
	
	Dir = TheInputHandler::Instance()->getMousePosition();
}

void Walker::draw(SDL_Renderer* renderer)
{
	m_BG[0]->draw(renderer);
	filledCircleRGBA(renderer, Dir->getX(), Dir->getY(), 15, 255, 255, 0, 200);
	m_vehicle->draw(renderer);
	m_St->draw(renderer);
	
	//m_baseGameEntity->draw(renderer);
}



