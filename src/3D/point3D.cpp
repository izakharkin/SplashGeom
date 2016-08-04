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
#include "point3D.hpp"

Point3D::Point3D()
	: x(0.0), y(0.0) {}

Point3D::Point3D(double _x, double _y, double _z)
	: x(_x), y(_y), z(_z) {}

std::ostream& operator << (std::ostream& o, const Point3D& p)
{
	o << p.x << ' ' << p.y << ' ' << p.z;
	return o;
}

std::istream& operator >> (std::istream& in, Point3D& new_point)
{
	in >> new_point.x >> new_point.y >> new_point.z;
	return in;
}

bool Point3D::operator == (const Point3D& b) const
{
	return this->x == b.x && this->y == b.y && this->z == b.z;
}

bool Point3D::operator != (const Point3D& b) const
{
	return !(*this == b);
}

bool Point3D::operator < (const Point3D& b) const
{
	return this->x < b.x - EPS || 
		   fabs(this->x - b.x) < EPS && this->y < b.y - EPS || 
		   fabs(this->x - b.x) < EPS &&  fabs(this->y - b.y) && this->z < b.z - EPS;
}

Point3D Point3D::operator + (const Point3D& b) const
{
	return Point3D(this->x + b.x, this->y + b.y, this->z + b.z);
}

Point3D Point3D::operator - (const Point3D& b) const
{
	return Point3D(this->x - b.x, this->y - b.y, this->z - b.z);
}

Point3D Point3D::operator * (double num) const
{
	return Point3D(this->x * num, this->y * num, this->z * num);
}

Point3D Point3D::operator / (double num) const
{
	return Point3D(this->x / num, this->y / num, this->z / num);
}

double Point3D::l1_distance(const Point3D& b) const
{
	return fabs(this->x - b.x) + fabs(this->y - b.y) + fabs(this->z - b.z);
}

double Point3D::l2_distance(const Point3D& b) const
{
	return sqrt((this->x - b.x) * (this->x - b.x) + (this->y - b.y) * (this->y - b.y) + (this->z - b.z) * (this->z - b.z));
}