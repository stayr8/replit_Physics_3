#define WIDTH (600)
#define HEIGHT (400)

#include "Walker.h"
#include "InputHandler.h"
#include <random>

std::random_device rd;

std::mt19937 gen(rd());

std::uniform_int_distribution<int> dis(0, 600);
std::uniform_int_distribution<int> dis2(0, 400);

Walker::Walker() 
{
	target = new Target(WIDTH - 50, HEIGHT - 50);
	pursuer = new Vehicle(50,50);

	d = new Vector2D(0, 0);
	steering = new Vector2D(0, 0);

	pause = false;
}

void Walker::update() 
{
	*steering = pursuer->pursue(target);
	pursuer->applyForce(steering);

	*d = pursuer->getPos() - target->getPos();
	float d2 = d->length();
	if (d2 < pursuer->getR() + target->getR())
	{
		target = new Target(dis(gen), dis2(gen));
	}

	pursuer->update();

	target->update();
	target->applyForce(steering);

}

void Walker::draw(SDL_Renderer* renderer)
{

	pursuer->draw(renderer);
	target->draw(renderer);
}

