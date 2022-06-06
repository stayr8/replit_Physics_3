#define WIDTH (600)
#define HEIGHT (400)

#include "SteeringBehavior.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <limits>

SteeringBehavior::SteeringBehavior(int x, int y) : maxSpeed(6), maxForce(0.4f),
r(16), radian(0), DistanceFromBoundary(0), DistAway(0), DistToClosest(0),
dist(0), dist2(0)
{
    pos = new Vector2D(x, y);
    vel = new Vector2D(0, 0);
    acc = new Vector2D(0, 0);
    force = new Vector2D(0, 0);
    rd1 = new Vector2D(1, 1);
    rd2 = new Vector2D(1, 1);
    rd3 = new Vector2D(1, 1);
    rotate = new Vector2D(0, 0);

    ToOb = new Vector2D(0, 0);

    BestHidingSpot = new Vector2D(0, 0);
    //HidingSpot = new Vector2D(0, 0);

    ToTarget = new Vector2D(0, 0);
    DesiredVelocity = new Vector2D(0, 0);
    DesiredVelocity2 = new Vector2D(0, 0);

    ToPursuer = new Vector2D(0, 0);
    VelTime = new Vector2D(0, 0);

    Distance = new Vector2D(0, 0);

}


Vector2D SteeringBehavior::Flee(Vector2D* TargetPos)
{
    *DesiredVelocity = *pos - *TargetPos;
    DesiredVelocity->normalize();
    *DesiredVelocity *= maxSpeed;
    *DesiredVelocity -= *vel;

    return *DesiredVelocity;
}

Vector2D SteeringBehavior::Evade(Vehicle* pursuer)
{
    *ToPursuer = pursuer->getPos() - *pos;

    const double ThreatRange = 100.0f;
    if ((ToPursuer->length() * ToPursuer->length()) > ThreatRange * ThreatRange)
    {
        return Vector2D(0, 0);
    }

    double LookAheadTime = ToPursuer->length() / (maxSpeed + pursuer->getMaxSpeed());

    *VelTime = pursuer->getPos() + pursuer->getVel() * LookAheadTime;


    return Flee(VelTime);
}

Vector2D SteeringBehavior::Arrive(Vector2D* TargetPos)
{
    *force = *TargetPos - *pos;
    dist = force->length();

    if (dist > 0)
    {
        const double DecelerationTweaker = 0.3f;
        double speed = dist / (50 * DecelerationTweaker);
        speed = std::min(speed, maxSpeed);
        *force *= speed / dist;
        *DesiredVelocity = *force;

        return *DesiredVelocity - *vel;
    }

    return Vector2D(0, 0);
}


Vector2D SteeringBehavior::Hide(Vehicle* hunter
    ,const std::vector<BaseGameEntity*>& obstacles)
{
    //DistToClosest = std::numeric_limits<double>::max();
    DistToClosest = 70;

    std::vector<BaseGameEntity*>::const_iterator curOb = obstacles.begin();
    std::vector<BaseGameEntity*>::const_iterator closest;

    while (curOb != obstacles.end())
    {
        Vector2D* HidingSpot = GetHidingPosition((*curOb)->getPos(),
                                       (*curOb)->getRadius(),
                                        hunter->getPos());

        *Distance = *HidingSpot - *pos;
        dist = Distance->length();
        //dist = (Distance->getX() * Distance->getX()) + (Distance->getY() * Distance->getY());
        printf("%lf\n", dist);
        if (dist < DistToClosest)
        {
            DistToClosest = dist;

            *BestHidingSpot = *HidingSpot;

            closest = curOb;
        }
        ++curOb;
    }

    //std::numeric_limits<float>::max()
    if (DistToClosest == 70)
    {
        return Evade(hunter);
    }
    return Arrive(BestHidingSpot);

}

Vector2D* SteeringBehavior::GetHidingPosition(const Vector2D& posOb
    , const double radiusOb
    , const Vector2D& posHunter)
{
    DistanceFromBoundary = 30.0;
    DistAway = radiusOb + DistanceFromBoundary;

    *ToOb = posOb - posHunter;
    ToOb->normalize();
    *ToOb *= DistAway;
    *ToOb += posOb;

    return ToOb;
}

void SteeringBehavior::applyForce(Vector2D* f)
{
    *acc += *f;
}


Vector2D SteeringBehavior::Radian(float x, float y, float radian)
{
    rotate = new Vector2D(0, 0);

    rotate->setX(cos(radian) * x - sin(radian) * y);
    rotate->setY(sin(radian) * x + cos(radian) * y);

    return *rotate;
}


void SteeringBehavior::edges()
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

void SteeringBehavior::update()
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

void SteeringBehavior::draw(SDL_Renderer* renderer)
{

    filledTrigonRGBA(renderer, rd1->getX() + pos->getX(),
        rd1->getY() + pos->getY(),
        rd2->getX() + pos->getX(),
        rd2->getY() + pos->getY(),
        rd3->getX() + pos->getX(),
        rd3->getY() + pos->getY(),
        255, 255, 255, 255);

}