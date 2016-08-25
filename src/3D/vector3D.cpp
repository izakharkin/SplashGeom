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
#include "vector3D.hpp"

Vector3D::Vector3D()
	: x1(), x2() {}

Vector3D::Vector3D(double _x1, double _x2, double _x3)
	: x1(_x1), x2(_x2), x3(_x3) {}

Vector3D::Vector3D(const Point3D& point_to)
	: x1(point_to.x), x2(point_to.y), x3(point_to.z) {}

Vector3D::Vector3D(const Point3D& point_from, const Point3D& point_to)
	: x1(point_to.x - point_from.x), x2(point_to.y - point_from.y), x3(point_to.z - point_from.z) {}

double Vector3D::Dot(const Vector3D& second_vec) const
{
	return (this->x1 * second_vec.x1 + this->x2 * second_vec.x2 + this->x3 * second_vec.x3);
}

double Vector3D::OrientedCCW(const Vector3D& second_vector) const
{
	return 0;
}

double Vector3D::Norm() const
{
	return sqrt(this->Dot(*this));
}

Vector3D Vector3D::Ortopair() const
{
	return Vector3D(-x2, x1, 0);
}

Point3D operator + (const Point3D& point_for_add, const Vector3D& vec_to_add)
{
	return Point3D(point_for_add.x + vec_to_add.x1, point_for_add.y + vec_to_add.x2, point_for_add.z + vec_to_add.x3);
}
