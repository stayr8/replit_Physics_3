#pragma once

#include "main.h"
#include "Vector2D.h"
#include "Vehicle.h"
#include <vector>

class BaseGameEntity
{
public:
	BaseGameEntity(float x, float y, float r2);
	void draw(SDL_Renderer* renderer);
	void update();

	Vector2D getPos() { return *pos; }
	int getRadius() { return r; }

private:
	Vector2D* pos;
	
	
	
	int r;
};