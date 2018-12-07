#pragma once
#include "..\Add_On\Vector2D.h"
#include <HAPI_lib.h>

using namespace HAPISPACE;
using namespace GM;
class Physics
{
public:
	Physics();
	virtual ~Physics();
	void CalcVelocity();
	
	Vector2D GetVelocity() { return velocity;};
	void SetDirection(Vector2D dir) { direction = dir; };
	void SetSpeed(float nSpeed) { speed = nSpeed; };
	float  GetSpeed() { return speed; };


private:
	Vector2D velocity;
	float speed ;
	Vector2D direction;
	DWORD deltaTime;

};

