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
#include "Segment3D.hpp"

Segment3D::Segment3D()
: a(), b() {}

Segment3D::Segment3D(const Point3D& _a, const Point3D& _b)
: a(_a), b(_b) {}

void Segment3D::Reverse()
{
	swap(a, b);
}

double Segment3D::Length() const
{
	return a.l2_distance(b);
}

Point3D Segment3D::Center() const
{
	return (this->a + this->b) * 0.5;
}

bool Segment3D::Point3DInBox(const Point3D& point) const
{
	double lower_x = std::min(a.x, b.x);
	double upper_x = std::max(a.x, b.x);
	double lower_y = std::min(a.y, b.y);
	double upper_y = std::max(a.y, b.y);
	double lower_z = std::min(a.z, b.z);
	double upper_z = std::max(a.z, b.z);

	return lower_x <= point.x && point.x <= upper_x && 
		   lower_y <= point.y && point.y <= upper_y &&
		   lower_z <= point.z && point.z <= upper_z;
}

Vector3D Segment3D::Direction() const
{
	return Vector3D(a, b);
}

Vector3D Segment3D::NormalVec() const
{
	return Line3D(*this).NormalVec();
}

bool Segment3D::Contains(const Point3D& point) const
{
	Line3D cur_line(this->a, this->b);
	return this->Point3DInBox(point) && cur_line.Contains(point);
}

Point3D Segment3D::GetIntersection(const Segment3D& second_seg) const
{
	Line3D first_line(*this);
	Line3D second_line(second_seg);

	Point3D intersect_point = first_line.GetIntersection(second_line);

	if (intersect_point == Point3D(-INF, -INF, -INF))
	{
		if (this->Point3DInBox(second_seg.a))
		{
			intersect_point = second_seg.a;
		}
		else if (this->Point3DInBox(second_seg.b))
		{
			intersect_point = second_seg.b;
		}
	}
	else
	{
		if (!(this->Point3DInBox(intersect_point) && second_seg.Point3DInBox(intersect_point)))
		{
			intersect_point = Point3D(INF, INF, INF);
		}
	}

	return intersect_point;
}

Point3D Segment3D::GetIntersection(const Line3D& line) const
{
	return line.GetIntersection(*this);
}

Point3D Segment3D::GetIntersection(const Ray3D& ray) const
{
	return ray.GetIntersection(*this);
}

bool Segment3D::HasIntersection(const Segment3D& second_seg) const
{
	return this->GetIntersection(second_seg) != Point3D(INF, INF, INF);
}

bool Segment3D::HasIntersection(const Line3D& line) const
{
	return line.HasIntersection(*this);
}

bool Segment3D::HasIntersection(const Ray3D& ray) const
{
	return ray.HasIntersection(*this);
}