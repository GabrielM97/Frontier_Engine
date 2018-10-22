#pragma once

#include<iostream>

using namespace std;


class Vector2D
{
public:

	float x;
	float y;

	Vector2D();
	Vector2D(float newX, float newY);

	float distance();
	float dotProduct(const Vector2D &v1, const Vector2D &v2);
	float crossProduct(const Vector2D &v1, const Vector2D &v2);
	void normalise(float &dist);

	~Vector2D();
	void setPos(float new_X, float new_Y)
	{
		x = new_X;
		y = new_Y;
	};

	Vector2D& operator +=(const Vector2D& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2D& operator -=(const Vector2D& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}
	Vector2D& operator *=(const Vector2D& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;

		return *this;
	}

	Vector2D& operator /=(const Vector2D& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	bool operator ==(const Vector2D& rhs)
	{
		if (x == rhs.x && y == rhs.y)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	bool operator !=(const Vector2D& rhs)
	{
		if (x != rhs.x && y != rhs.y)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

protected:

private:
};

inline std::ostream & operator <<(std::ostream& os, const Vector2D&v)
{
	os << "[" << v.x << "," << v.y << "]";
	return os;
}

inline Vector2D operator + (Vector2D lhs, const Vector2D & rhs)
{
	lhs += rhs;
	return lhs;
}
inline Vector2D operator + (Vector2D lhs, const int & rhs)
{
	lhs.x += rhs;
	lhs.y += rhs;
	return lhs;
}
inline Vector2D  operator - (Vector2D lhs, const Vector2D & rhs)
{
	lhs -= rhs;
	return lhs;
}

inline Vector2D  operator / (Vector2D lhs, const Vector2D & rhs)
{
	lhs /= rhs;
	return lhs;
}

inline Vector2D  operator * (Vector2D lhs, const Vector2D & rhs)
{
	lhs *= rhs;
	return lhs;
}
inline Vector2D operator * (Vector2D lhs, float rhs)
{


	return Vector2D(lhs.x*rhs, lhs.y * rhs);
}

