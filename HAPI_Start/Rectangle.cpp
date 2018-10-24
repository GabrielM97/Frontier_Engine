#include "Rectangle.h"


namespace GM
{
	void Rectangle::Translate(int dx, int dy)
	{
		left += dx;
		right = +dx;
		top += dy;
		bottom += dy;
	}

	void Rectangle::clipToRect(const Rectangle & otherRect)
	{
		if (left < otherRect.left)
			left = otherRect.left;

		if (top < otherRect.top)
			top = otherRect.top;

		if (right > otherRect.right)
			right = otherRect.right;

		if (bottom > otherRect.bottom)
			bottom = otherRect.bottom;
	}

	Rectangle::~Rectangle()
	{
	}
}



