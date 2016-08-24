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
	
}

Plane::Plane(const Point3D& point, const Vector3D& direction1, const Vector3D& direction_2) {}

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

Point3D Plane::GetIntersection(const Line3D& second_line) const {
    return Point3D();
}
Point3D Plane::GetIntersection(const Segment3D& segment) const {
    return Point3D();
}
Point3D Plane::GetIntersection(const Ray3D& ray) const {
    return Point3D();
}
