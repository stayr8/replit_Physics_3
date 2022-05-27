#define WIDTH (600)
#define HEIGHT (400)

#include "Target.h"

Target::Target(float x, float y) : Vehicle(x, y)
{

}

void Target::update()
{
	*vel *= 4;

	edges();
	Vehicle::update();
}

void Target::draw(SDL_Renderer* renderer)
{
	circleRGBA(renderer, pos->getX(), pos->getY(), r * 2, 0, 0, 255, 255);
}

void Target::applyForce(Vector2D* force)
{
	Vehicle::applyForce(force);
}


void Target::edges()
{
	if (pos->getX() > WIDTH - r) {
		vel->setX(vel->getX() * -1);
		pos->setX(WIDTH - r);
	}else if (pos->getX() < r) {
		vel->setX(vel->getX() * -1);
		pos->setX(r);
	}

	if (pos->getY() > HEIGHT - r) {
		vel->setY(vel->getY() * -1);
		pos->setY(HEIGHT - r);
	}
	else if (pos->getY() < r) {
		vel->setY(vel->getY() * -1);
		pos->setY(r);
	}

	
}