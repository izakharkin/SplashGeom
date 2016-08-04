// Splash (c) - open-source C++ library for geometry and linear algebra.
// Copyright (c) 2016, Ilya Zakharkin, Elena Kirilenko and Nadezhda Kasimova.
// All rights reserved.
/*
	This file is part of Splash.

	Splash is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Splash is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Splash.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Segment2D.hpp"

Segment2D::Segment2D()
	: a(), b() {}

Segment2D::Segment2D(const Point2D& _a, const Point2D& _b)
	: a(_a), b(_b) {}

void Segment2D::Reversr()
{
	swap(a, b);
}

double Segment2D::Length() const
{
	return a.l2_distance(b);
}

Point2D Segment2D::Center() const
{
	return (this->a + this->b) * 0.5;
}

bool Segment2D::Point2DInBox(const Point2D& point) const
{
	double lower_x = std::min(a.x, b.x);
	double upper_x = std::max(a.x, b.x);
	double lower_y = std::min(a.y, b.y);
	double upper_y = std::max(a.y, b.y);

	return lower_x <= point.x && point.x <= upper_x && lower_y <= point.y && point.y <= upper_y;
}

Vector2D Segment2D::Dir() const
{
	return Vector2D(a, b);
}

bool Segment2D::Contains(const Point2D& point) const
{
	Line2D cur_line(this->a, this->b);
	return this->Point2DInBox(point) && cur_line.Contains(point);
}

Point2D Segment2D::Intersect(const Segment2D& second_seg) const
{
	Line2D first_line(*this);
	Line2D second_line(second_seg);
	
	Point2D intersect_point = first_line.Intersect(second_line);

	if (intersect_point == Point2D(-INF, -INF))
	{
		if (this->Point2DInBox(second_seg.a))
		{
			intersect_point = second_seg.a;
		}
		else if (this->Point2DInBox(second_seg.b))
		{
			intersect_point = second_seg.b;
		}
	}
	else
	{
		if ( !(this->Point2DInBox(intersect_point) && second_seg.Point2DInBox(intersect_point)) )
		{
			intersect_point = Point2D(INF, INF);
		}
	}

	return intersect_point;
}

Point2D Segment2D::Intersect(const Line2D& line) const
{
	return line.Intersect(*this);
}

Point2D Segment2D::Intersect(const Ray2D& ray) const
{
	return ray.Intersect(*this);
}