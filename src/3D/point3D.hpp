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
#ifndef POINT3D_HPP_
#define POINT3D_HPP_

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

class Point3D
{
public:
	double x;
	double y;
	double z;

	Point3D();
	Point3D(double _x, double _y, double _z);

	double l1_distance(const Point3D&) const;
	double l2_distance(const Point3D&) const;

	Point3D operator + (const Point3D&) const;
	Point3D operator - (const Point3D&) const;
	Point3D operator * (double) const;
	Point3D operator / (double) const;

	bool operator == (const Point3D&) const;
	bool operator != (const Point3D&) const;
	bool operator < (const Point3D&) const;

	friend std::ostream& operator << (std::ostream&, const Point3D&);
	friend std::istream& operator >> (std::istream&, Point3D&);
};

const Point3D kInfPoint3D = Point3D(INF, INF, INF);
const Point3D kNegInfPoint3D = Point3D(-INF, -INF, -INF);

#endif /*POINT3D_HPP_*/
