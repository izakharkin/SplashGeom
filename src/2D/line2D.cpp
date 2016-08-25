// SplashGeom (c) - open-source C++ library for geometry and linear algebra.
// Copyright (c) 2016, Ilya Zakharkin, Elena Kirilenko and Nadezhda Kasimova.
// All rights reserved.
/*
	This file is part of SplashGeom.

	SplashGeom is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	SplashGeom is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with SplashGeom. If not, see <http://www.gnu.org/licenses/>.
*/
#include "line2D.hpp"

Line2D::Line2D()
	: A(0.0), B(0.0), C(0.0) {}

Line2D::Line2D(const Ray2D& ray)
	: Line2D(ray.pos_, *ray.dir_) {}

Line2D::Line2D(const Point2D& a, const Point2D& b)
	: A(b.y - a.y), B(a.x - b.x), C(-A * a.x - B * a.y) {}

Line2D::Line2D(const Segment2D& segment)
	: Line2D(segment.a, segment.b) {}

Line2D::Line2D(const Point2D& point, const Vector2D& direction)
	: Line2D(point, point + direction) {}


double Line2D::GetA() const
{
	return A;
}

double Line2D::GetB() const
{
	return B;
}

double Line2D::GetC() const
{
	return C;
}

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

Vector2D Line2D::NormalVec() const
{
	return Vector2D(this->A, this->B);
}

double Line2D::Distance(const Point2D& point) const
{
	return PointIntoLine2D(point) / this->NormalVec().Norm();
}

bool Line2D::Contains(const Point2D& point) const
{
	return this->Sign(point) == 0;
}

Point2D Line2D::GetIntersection(const Line2D& second_line) const
{
	double cross_prod_norms = Vector2D(this->A, this->B).OrientedCCW(Vector2D(second_line.A, second_line.B));
	Point2D intersect_point;
	if (fabs(cross_prod_norms) <= EPS) /* A1 / A2 == B1 / B2 */ {
		if (fabs(this->B * second_line.C - second_line.B * this->C) <= EPS) /* .. == C1 / C2 */ {
			intersect_point = kNegInfPoint2D;
		} else {
			intersect_point = kInfPoint2D;
		}
	} else {
		double res_x = (second_line.C * this->B - this->C * second_line.B) / cross_prod_norms;
		double res_y = (second_line.A * this->C - this->A * second_line.C) / cross_prod_norms;
		intersect_point = Point2D(res_x, res_y);
	}
	return intersect_point;
}

Point2D Line2D::GetIntersection(const Segment2D& segment) const
{
	Line2D second_line(segment);
	Point2D intersect_point = this->GetIntersection(second_line);
	if (intersect_point == kNegInfPoint2D) {
		intersect_point = segment.b;
	} else if (intersect_point != kInfPoint2D && !segment.Contains(intersect_point)) {
		intersect_point = kInfPoint2D;
	}
	return intersect_point;
}

Point2D Line2D::GetIntersection(const Ray2D& ray) const
{
	Line2D second_line(ray);
	Point2D intersect_point = this->GetIntersection(second_line);
	if (intersect_point == kNegInfPoint2D) {
		intersect_point = ray.pos_;
	} else if (intersect_point != kInfPoint2D && !ray.Contains(intersect_point)) {
		intersect_point = kInfPoint2D;
	}
	return intersect_point;
}

bool Line2D::HasIntersection(const Line2D& second_line) const
{
	return this->GetIntersection(second_line) != kInfPoint2D;
}

bool Line2D::HasIntersection(const Segment2D& segment) const
{
	return this->GetIntersection(segment) != kInfPoint2D;
}

bool Line2D::HasIntersection(const Ray2D& ray) const
{
	return this->GetIntersection(ray) != kInfPoint2D;
}


