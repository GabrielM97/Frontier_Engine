#pragma once

namespace GM
{
	class Rectangle
	{
	public:

		int left{ 0 }, top{ 0 }, right{ 0 }, bottom{ 0 };
		Rectangle() = default;
		Rectangle(int l, int t, int r, int b) : left(l), top(t), right(r), bottom(b) {};
		Rectangle(int width, int height) : right(width), bottom(height) {};

		int Width()const { return right - left; };
		int Height() const { return bottom - top; };

		void Translate(int dx, int dy);

		void clipToRect(const Rectangle &otherRect);

		virtual ~Rectangle();
	};
}


