#pragma once

#include "main.h"
#include "Vector2D.h"
#include "Vehicle.h"
#include "BaseGameEntity.h"
#include "SteeringBehavior.h"
#include <vector>


class Walker
{

public:
	Walker();
	void draw(SDL_Renderer* renderer);
	void update();
	

private:
	Vector2D* Dir;
	Vector2D* steering;
	Vector2D* Force;

	Vehicle* m_vehicle;

	SteeringBehavior* m_St;

	std::vector<BaseGameEntity*> m_BG;

	
};