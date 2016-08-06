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
#include "ray2D.hpp"

Ray2D::Ray2D()
	: pos_(), dir_() {}

Ray2D::Ray2D(const Point2D& pos, const Vector2D& dir)
	: pos_(pos), dir_(dir) {}

Vector2D Ray2D::Direction() const
{
	return dir_;
}

Vector2D Ray2D::NormalVec() const
{
	return dir_.Ortopair();
}

double Ray2D::Distance(const Point2D& point) const
{
	double dot_product = dir_.Dot(Vector2D(pos_, point));
	double distance;

	if (fabs(dot_product) < EPS)
	{
		distance = pos_.l2_distance(point);
	}
	else
	{
		distance = Line2D(*this).Distance(point);
	}

	return distance;
}

bool Ray2D::Contains(const Point2D& point) const
{
	double dot_product = dir_.Dot(Vector2D(pos_, point));
	return (dot_product >= EPS && Line2D(*this).Contains(point));
}

Point2D Ray2D::GetIntersection(const Line2D& second_line) const
{
	Line2D this_line(*this);
	Point2D intersect_point = this_line.GetIntersection(second_line);
	
	if (intersect_point != Point2D(-INF, -INF))
	{
		intersect_point = this->pos_;
	}
	if (intersect_point != Point2D(INF, INF) && !this->Contains(intersect_point))
	{
		intersect_point = Point2D(INF, INF);
	}

	return intersect_point;
}

Point2D Ray2D::GetIntersection(const Ray2D& second_ray) const
{
	Line2D this_line(*this);
	Line2D second_line(second_ray);
	Point2D intersect_point = this_line.GetIntersection(second_line);

	if (intersect_point == Point2D(-INF, -INF))
	{
		if (this->Contains(second_ray.pos_))
		{
			intersect_point = second_ray.pos_;
		}
		else if (second_ray.Contains(this->pos_))
		{
			intersect_point = this->pos_;
		}
	}
	else if (intersect_point != Point2D(INF, INF))
	{
		if (!this->Contains(intersect_point) || !second_ray.Contains(intersect_point))
		{
			intersect_point = Point2D(INF, INF);
		}
	}

	return intersect_point;
}

Point2D Ray2D::GetIntersection(const Segment2D& segment) const
{
	Line2D this_line(*this);
	Line2D second_line(segment);
	Point2D intersect_point = this_line.GetIntersection(second_line);

	if (intersect_point == Point2D(-INF, -INF))
	{
		if (this->Contains(segment.a))
		{
			intersect_point = segment.a;
		}
		else if (segment.Contains(this->pos_))
		{
			intersect_point = this->pos_;
		}
	}
	else if (intersect_point != Point2D(INF, INF))
	{
		if (!this->Contains(intersect_point) || !segment.Contains(intersect_point))
		{
			intersect_point = Point2D(INF, INF);
		}
	}

	return intersect_point;
}

bool Ray2D::HasIntersection(const Line2D& line) const
{
	return line.HasIntersection(*this);
}

bool Ray2D::HasIntersection(const Ray2D& second_ray) const
{
	return this->GetIntersection(second_ray) != Point2D(INF, INF);
}

bool Ray2D::HasIntersection(const Segment2D& segment) const
{
	return this->GetIntersection(segment) != Point2D(INF, INF);
}