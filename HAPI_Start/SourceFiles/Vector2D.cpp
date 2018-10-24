#include "Vector2D.H"
#include <math.h>
#include "Vector2D.h"

namespace GM
{
	Vector2D::Vector2D()
	{
		x = 0;
		y = 0;
	}
	Vector2D::Vector2D(float newX, float newY) : x{ newX }, y{ newY }
	{

	}

	float Vector2D::dotProduct(const Vector2D &v1, const Vector2D &v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	float Vector2D::crossProduct(const Vector2D &v1, const Vector2D &v2)
	{
		return (v1.x * v2.x) - (v1.y * v2.y);
	}

	float Vector2D::distance()
	{
		return sqrt((x*x) + (y*y));
	}

	void Vector2D::normalise(float &dist)
	{
		x /= dist;
		y /= dist;
	}

	Vector2D::~Vector2D()
	{
	}
}


