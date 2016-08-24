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
	along with Splash. If not, see <http://www.gnu.org/licenses/>.
*/
#include "plane.hpp"

Plane::Plane()
	: A(0.0), B(0.0), C(0.0), D(0.0) {}

Plane::Plane(const Point3D& p1, const Point3D& p2, const Point3D& p3)  
{
	A = p1.y * (p2.x - p3.z) + p2.y * (p3.z - p1.z) + p3.y * (p1.z - p2.z);
	B = p1.z * (p2.x - p3.x) + p2.z * (p3.x - p1.x) + p3.z * (p1.x - p2.x);
	C = p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y);
	D = - p1.x * (p2.y * p3.z - p3.y * p2.z) - p2.x * (p3.y * p1.z - p1.y * p3.z) - p3.x * (p1.y * p2.z - p2.y * p1.z);
}

Plane::Plane(const Point3D& point, const Vector3D& direction_1, const Vector3D& direction_2)
{
	A = direction_1.x2 * direction_2.x3 - direction_2.x2 * direction_1.x3;
	B = direction_2.x1 * direction_1.x3 - direction_1.x1 * direction_2.x3;
	C = direction_1.x1 * direction_2.x2 - direction_2.x1 * direction_1.x2;
	D = point.x * A - point.y * B - point.z * C;
}

double Plane::PointIntoPlane(const Point3D& point) const
{
	return A * point.x + B * point.y + C * point.z + D;
}

int Plane::Sign(const Point3D& point) const
{
	double val = this->PointIntoPlane(point);
	return (fabs(val) <= EPS ? 0 : (val > 0 ? 1 : -1));
}

Vector3D Plane::NormalVec() const
{
	return Vector3D(this->A, this->B, this->C);
}

double Plane::Distance(const Point3D& point) const
{
	return PointIntoPlane(point) / this->NormalVec().Norm();
}

bool Plane::Contains(const Point3D& point) const
{
	return this->Sign(point) == 0;
}

Point3D Plane::GetIntersection(const Line3D& second_line) const
{
	double denominator = this->A * second_line.GetVec().x1 + this->B * second_line.GetVec().x2 + this->C * second_line.GetVec().x3;
	if (denominator == 0)
		return Point3D(INF, INF, INF);//no intersections
	double parametr = -(this->A * second_line.GetPoint().x + this->B * second_line.GetPoint().y + this->C * second_line.GetPoint().y + this->D) / denominator;
    return Point3D(second_line.GetPoint().x + second_line.GetVec().x1 * parametr, second_line.GetPoint().y + second_line.GetVec().x2 * parametr, second_line.GetPoint().z + second_line.GetVec().x3 * parametr);
}

Point3D Plane::GetIntersection(const Segment3D& segment) const
{
    return Point3D();
}

Point3D Plane::GetIntersection(const Ray3D& ray) const
{
    return Point3D();
}