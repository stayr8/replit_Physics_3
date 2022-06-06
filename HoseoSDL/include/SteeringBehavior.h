#pragma once

#include "main.h"
#include "Vehicle.h"
#include "Vector2D.h"
#include <vector>
#include "BaseGameEntity.h"

class SteeringBehavior
{

public:
	SteeringBehavior(int x, int y);
	void draw(SDL_Renderer* renderer);
	void update();
	void applyForce(Vector2D* f);
	void edges();
	Vector2D Radian(float x, float y, float r);

	Vector2D* GetHidingPosition(const Vector2D& posOb
		, const double radiusOb
		, const Vector2D& posHunter);
	Vector2D Hide(Vehicle* hunter
		, const std::vector<BaseGameEntity*>& obstacles);

	Vector2D Arrive(Vector2D* TargetPos);
	Vector2D Evade(Vehicle* pursuer);

	Vector2D Flee(Vector2D* TargetPos);

private:
	Vector2D* pos;
	Vector2D* vel;
	Vector2D* acc;
	Vector2D* force;
	Vector2D* rd1;
	Vector2D* rd2;
	Vector2D* rd3;
	Vector2D* rotate;

	Vector2D* ToOb;

	Vector2D* BestHidingSpot;
	//Vector2D* HidingSpot;

	Vector2D* ToTarget;
	Vector2D* DesiredVelocity;
	Vector2D* DesiredVelocity2;

	Vector2D* ToPursuer;
	Vector2D* VelTime;

	Vector2D* Distance;

	double maxSpeed;
	double maxForce;
	int r;

	double radian;
	
	double DistanceFromBoundary;
	double DistAway;

	double DistToClosest;
	double dist;
	double dist2;
};