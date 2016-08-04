// Splash (c) - open-source C++ library for geometry and linear algebra
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
#include "line2D.hpp"

Line2D::Line2D()
	: A(0.0), B(0.0), C(0.0) {}

Line2D::Line2D(const Ray2D& ray)
	: Line2D(ray.pos_, ray.dir_) {}

Line2D::Line2D(const Segment2D& seg)
{
	A = seg.b.y - seg.a.y;
	B = seg.a.x - seg.b.x;
	C = -A * seg.a.x - B * seg.a.y;
}

Line2D::Line2D(const Point2D& a, const Point2D& b)
{
	A = b.y - a.y;
	B = a.x - b.x;
	C = -A * a.x - B * a.y;
}

Line2D::Line2D(const Point2D& point, const Vector2D& direction)
	: Line2D(point, point + direction) {}

double Line2D::PointIntoLine2D(const Point2D& point) const
{
	return A * point.x + B * point.y + C;
}

int Line2D::Sign(const Point2D& point) const
{
	double val = this->PointIntoLine2D(point);
	return (fabs(val) <= EPS ? 0 : (val > 0 ? 1 : -1));
}

Vector2D Line2D::Direction() const
{
	return Vector2D(-this->B, this->A);
}

Vector2D Line2D::Normal() const
{
	return Vector2D(this->A, this->B);
}

double Line2D::Distance(const Point2D& point) const
{
	return PointIntoLine2D(point) / this->Normal().Norm();
}

bool Line2D::Contains(const Point2D& point) const
{
	return this->Sign(point) == 0;
}

Point2D Line2D::Intersect(const Line2D& second_line) const
{
	double cross_prod_norms = Vector2D(this->A, this->B).OrientedCCW(Vector2D(second_line.A, second_line.B));
	Point2D intersect_point;

	if (cross_prod_norms <= EPS) // A1 / A2 == B1 / B2
	{
		if (this->B * second_line.C == second_line.B * this->C) // .. == C1 / C2
			intersect_point = Point2D(-INF, -INF);
		else
			intersect_point = Point2D(INF, INF);
	}
	else
	{
		double res_y = (this->C - second_line.C) / cross_prod_norms * this->A;
		double res_x = -(this->B * res_y + this->C) / this->A;
		intersect_point = Point2D(res_x, res_y);
	}

	return intersect_point;
}

Point2D Line2D::Intersect(const Segment2D& segment) const
{
	Line2D second_line(segment);
	Point2D intersect_point = this->Intersect(second_line);

	if (intersect_point == Point2D(-INF, -INF))
	{
		intersect_point = segment.a;
	}
	else if (intersect_point != Point2D(INF, INF) && !segment.Contains(intersect_point))
	{
		intersect_point = Point2D(INF, INF);
	}

	return intersect_point;
}

Point2D Line2D::Intersect(const Ray2D& ray) const
{
	Line2D second_line(ray);
	Point2D intersect_point = this->Intersect(second_line);

	if (intersect_point == Point2D(-INF, -INF))
	{
		intersect_point = ray.pos_;
	}
	else if (intersect_point != Point2D(INF, INF) && !ray.Contains(intersect_point))
	{
		intersect_point = Point2D(INF, INF);
	}

	return intersect_point;
}


