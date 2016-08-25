// SplashGeom (c) - open-source C++ library for geometry and linear algebra.
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
	: M(0.0, 0.0, 0.0), vect_direction(Point3D(0.0, 0.0, 0.0), Point3D(0.0, 0.0, 0.0)) {}

Line3D::Line3D(const Ray3D& ray)
	: Line3D(ray.pos_, ray.dir_) {}

Line3D::Line3D(const Segment3D& seg)
	: Line3D(seg.a, Vector3D(seg.b, seg.a)) {}

Line3D::Line3D(const Point3D& a, const Point3D& b)
{
	this->M = a;
	this->vect_direction = Vector3D(a, b);
}

Line3D::Line3D(const Point3D& point, const Vector3D& direction)
	: M(point), vect_direction(direction) {}

Vector3D Line3D::Direction() const
{
	return this->vect_direction;
}

Vector3D Line3D::GetVec() const
{
	return this->vect_direction;
}

Point3D Line3D::GetPoint() const
{
	return this->M;
}

Vector3D Line3D::NormalVec() const
{
	double m = 1.0;
	if (this->vect_direction.x1 != 0)
	{
		m = -vect_direction.x2 / (vect_direction.x1 + vect_direction.x3);
		return Vector3D(m, 1, m);
	}
	if (this->vect_direction.x2 != 0 || this->vect_direction.x3 != 0)
	{
		m = -vect_direction.x1 / (vect_direction.x2 + vect_direction.x3);
		return Vector3D(m, 1, m);
	}
	return Vector3D(m, m, m);
}

double Line3D::Distance(const Point3D& point) const
{
	double a = this->vect_direction.x1;
	double b = this->vect_direction.x2;
	double c = this->vect_direction.x3;

	double det1 = (point.y - this->M.y) * c - b * (point.z - this->M.z);
	double det2 = (point.z - this->M.z) * a - c * (point.x - this->M.x);
	double det3 = (point.x - this->M.x) * b - a * (point.y - this->M.y);

	double dist = sqrt((det1 * det1 + det2 * det2 + det3 * det3) / (a * a + b * b + c * c));
	return dist / this->NormalVec().Norm();
}

bool Line3D::Contains(const Point3D& point) const
{
	double t1 = (point.x - this->M.x) / this->vect_direction.x1;
	double t2 = (point.y - this->M.y) / this->vect_direction.x2;
	double t3 = (point.z - this->M.z) / this->vect_direction.x3;
	return (t1 == t2) && (t2 == t3);
}

Point3D Line3D::GetIntersection(const Line3D& second_line) const
{
	double denominator_x = (this->vect_direction.x2 * second_line.vect_direction.x1 - second_line.vect_direction.x2 * this->vect_direction.x1);
	double denominator_y = (this->vect_direction.x1 * second_line.vect_direction.x2 - second_line.vect_direction.x1 * this->vect_direction.x2);
	double denominator_z = (this->vect_direction.x2 * second_line.vect_direction.x3 - second_line.vect_direction.x2 * this->vect_direction.x3);
	
	if (denominator_x * denominator_y * denominator_z == 0)
		return Point3D(INF, INF, INF);

	Point3D point;
	point.x = (this->M.x * this->vect_direction.x2 * second_line.vect_direction.x1 - second_line.M.x * second_line.vect_direction.x2 * this->vect_direction.x1
		- this->M.y * this->vect_direction.x1 * second_line.vect_direction.x1 + second_line.M.y * this->vect_direction.x1 * second_line.vect_direction.x1) / denominator_x;
	point.y = (this->M.y * this->vect_direction.x1 * second_line.vect_direction.x2 - second_line.M.y * second_line.vect_direction.x1 * this->vect_direction.x2
		- this->M.x * this->vect_direction.x2 * second_line.vect_direction.x2 + second_line.M.x * this->vect_direction.x2 * second_line.vect_direction.x2) / denominator_y;
	point.z = (this->M.z * this->vect_direction.x2 * second_line.vect_direction.x3 - second_line.M.z * second_line.vect_direction.x2 * this->vect_direction.x3
		- this->M.y * this->vect_direction.x3 * second_line.vect_direction.x3 + second_line.M.y * this->vect_direction.x3 * second_line.vect_direction.x3) / denominator_z;
	
	return point;
}

Point3D Line3D::GetIntersection(const Segment3D& segment) const
{
	Line3D second_line(segment);
	Point3D intersect_point = this->GetIntersection(second_line);
	if (intersect_point != Point3D(INF, INF, INF) && !segment.Contains(intersect_point)) {
		intersect_point = Point3D(INF, INF, INF);
	}
	return intersect_point;
}

Point3D Line3D::GetIntersection(const Ray3D& ray) const
{
	Line3D second_line(ray);
	Point3D intersect_point = this->GetIntersection(second_line);
	if (intersect_point != Point3D(INF, INF, INF) && !ray.Contains(intersect_point)) {
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


