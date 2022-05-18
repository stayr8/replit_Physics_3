#pragma once

#include "Vehicle.h"
#include "Vector2D.h"
#include "main.h"


class Target : public Vehicle
{
public:
	Target(float x, float y);
	virtual void update();
	virtual void draw(SDL_Renderer* renderer);
	virtual void applyForce(Vector2D* force);
	virtual void edges();

private:

};