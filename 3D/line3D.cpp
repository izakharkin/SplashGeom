// Splash (c) - open-source C++ library for geometry and linear algebra.
// Copyright (c) 3016, Ilya Zakharkin, Elena Kirilenko and Nadezhda Kasimova.
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
	along with Splash. If not, see <http://www.gnu.org/licenses/>.
*/
#include "line3D.hpp"

Line3D::Line3D()
	: A(0.0), B(0.0), C(0.0) {}

Line3D::Line3D(const Ray3D& ray)
	: Line3D(ray.pos_, ray.dir_) {}

Line3D::Line3D(const Segment3D& seg)
{
	A = seg.b.y - seg.a.y;
	B = seg.a.x - seg.b.x;
	C = -A * seg.a.x - B * seg.a.y;
}

Line3D::Line3D(const Point3D& a, const Point3D& b)
{
	A = b.y - a.y;
	B = a.x - b.x;
	C = -A * a.x - B * a.y;
}

Line3D::Line3D(const Point3D& point, const Vector3D& direction)
	: Line3D(point, point + direction) {}

double Line3D::PointIntoLine3D(const Point3D& point) const
{
	return A * point.x + B * point.y + C;
}

int Line3D::Sign(const Point3D& point) const
{
	double val = this->PointIntoLine3D(point);
	return (fabs(val) <= EPS ? 0 : (val > 0 ? 1 : -1));
}

Vector3D Line3D::Direction() const
{
	return Vector3D(-this->B, this->A, 0);
}

Vector3D Line3D::NormalVec() const
{
	return Vector3D(this->A, this->B, 0);
}

double Line3D::Distance(const Point3D& point) const
{
	return PointIntoLine3D(point) / this->NormalVec().Norm();
}

bool Line3D::Contains(const Point3D& point) const
{
	return this->Sign(point) == 0;
}

Point3D Line3D::GetIntersection(const Line3D& second_line) const
{
	double cross_prod_norms = Vector3D(this->A, this->B, 0).OrientedCCW(Vector3D(second_line.A, second_line.B, 0));
	Point3D intersect_point;
	if (cross_prod_norms <= EPS) /* A1 / A2 == B1 / B2 */ {
		if (this->B * second_line.C == second_line.B * this->C) /* .. == C1 / C2 */ {
			intersect_point = Point3D(-INF, -INF, -INF);
		} else {
			intersect_point = Point3D(INF, INF, INF);
		}
	} else {
		double res_y = (this->C - second_line.C) / cross_prod_norms * this->A;
		double res_x = -(this->B * res_y + this->C) / this->A;
		intersect_point = Point3D(res_x, res_y, 0);
	}
	return intersect_point;
}

Point3D Line3D::GetIntersection(const Segment3D& segment) const
{
	Line3D second_line(segment);
	Point3D intersect_point = this->GetIntersection(second_line);
	if (intersect_point == Point3D(-INF, -INF, -INF)) {
		intersect_point = segment.a;
	} else if (intersect_point != Point3D(INF, INF, INF) && !segment.Contains(intersect_point)) {
		intersect_point = Point3D(INF, INF, INF);
	}
	return intersect_point;
}

Point3D Line3D::GetIntersection(const Ray3D& ray) const
{
	Line3D second_line(ray);
	Point3D intersect_point = this->GetIntersection(second_line);
	if (intersect_point == Point3D(-INF, -INF, -INF)) {
		intersect_point = ray.pos_;
	} else if (intersect_point != Point3D(INF, INF, INF) && !ray.Contains(intersect_point)) {
		intersect_point = Point3D(INF, INF, INF);
	}
	return intersect_point;
}

bool Line3D::HasIntersection(const Line3D& second_line) const
{
	return this->GetIntersection(second_line) != Point3D(INF, INF, INF);
}

bool Line3D::HasIntersection(const Segment3D& segment) const
{
	return this->GetIntersection(segment) != Point3D(INF, INF, INF);
}

bool Line3D::HasIntersection(const Ray3D& ray) const
{
	return this->GetIntersection(ray) != Point3D(INF, INF, INF);
}


