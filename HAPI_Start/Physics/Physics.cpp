#include "Physics.h"



Physics::Physics()
{
}


Physics::~Physics()
{
}

void Physics::CalcVelocity()
{
	velocity = direction * speed;
}
