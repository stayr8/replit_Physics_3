#define WIDTH (600)
#define HEIGHT (400)

#include "Vehicle.h"
#include <math.h>
#include <iostream>
#include <algorithm>

Vehicle::Vehicle(int x, int y) : maxSpeed(6), maxForce(0.4f),
r(16), radian(0), slowRadius(0), distance(0), desiredSpeed(0), v(0)
{

    pos = new Vector2D(x, y);
    vel = new Vector2D(0, 0);
    acc = new Vector2D(0, 0);
    force = new Vector2D(0, 0);
    rd1 = new Vector2D(1, 1);
    rd2 = new Vector2D(1, 1);
    rd3 = new Vector2D(1, 1);
    rotate = new Vector2D(0, 0);
    DesiredVelocity = new Vector2D(0, 0);
    Zero = new Vector2D(0, 0);

}

void Vehicle::update()
{
    *vel += *acc;
    vel->limit(maxSpeed);
    *pos += *vel;
    *acc *= 0;

    radian = atan2(vel->getY(), vel->getX());

    *rd1 = Radian(-r, -r / 2, radian);
    *rd2 = Radian(-r, r / 2, radian);
    *rd3 = Radian(r, 0, radian);

    edges();
}

void Vehicle::draw(SDL_Renderer* renderer)
{

    filledTrigonRGBA(renderer, rd1->getX() + pos->getX(), rd1->getY() + pos->getY(), rd2->getX() + pos->getX(), rd2->getY() + pos->getY(), rd3->getX() + pos->getX(), rd3->getY() + pos->getY(), 255, 255, 255, 255);

}

Vector2D Vehicle::Radian(float x, float y, float radian)
{
    rotate = new Vector2D(0, 0);

    rotate->setX(cos(radian) * x - sin(radian) * y);
    rotate->setY(sin(radian) * x + cos(radian) * y);

    return *rotate;
}


void Vehicle::applyForce(Vector2D* f)
{
    *acc += *f;
}

Vector2D Vehicle::arrive(Vector2D* target)
{
    return seek(target, true);
}


Vector2D Vehicle::seek(Vector2D* target, bool arrival)
{
    *force = *target - *pos;
    double dist = force->length();

    if (dist > 0)
    {
        const double DecelerationTweaker = 1.0f;
        double speed = dist / (15 * DecelerationTweaker);
        speed = std::min(speed, maxSpeed);
        *force *= speed;
        *force /= dist;
        DesiredVelocity = force;
        *DesiredVelocity -= *vel;

        return *DesiredVelocity;
    }

    return *Zero;

}


void Vehicle::edges()
{
    if (pos->getX() > WIDTH + r)
    {
        pos->setX(r);
    }
    else if (pos->getX() < -r)
    {
        pos->setX(WIDTH + r);
    }
    if (pos->getY() > HEIGHT + r)
    {
        pos->setY(-r);
    }
    else if (pos->getY() < -r)
    {
        pos->setY(HEIGHT + r);
    }
}