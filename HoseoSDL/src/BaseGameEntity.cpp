#include "BaseGameEntity.h"
#include <math.h>

BaseGameEntity::BaseGameEntity(float x, float y, float r2)
{
    pos = new Vector2D(x, y);
    
    r = r2;
}

void BaseGameEntity::update()
{
   
}

void BaseGameEntity::draw(SDL_Renderer* renderer)
{

    filledCircleRGBA(renderer, pos->getX(), pos->getY(), r, 255, 255, 255, 255);

}


