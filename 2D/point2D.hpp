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
#ifndef POINT2D_HPP_
#define POINT2D_HPP_

#include "splash_forward.hpp"
#include "splash_utils.hpp"

class Point2D
{
public:
	double x;
	double y;

	Point2D();
	Point2D(double _x, double _y);

	double l1_distance(const Point2D&) const;
	double l2_distance(const Point2D&) const;

	Point2D operator + (const Point2D&) const;
	Point2D operator - (const Point2D&) const;
	Point2D operator * (double) const;
	Point2D operator / (double) const;

	Point2D operator - () const;

	bool operator == (const Point2D&) const;
	bool operator != (const Point2D&) const;
	bool operator < (const Point2D&) const;

	friend std::ostream& operator << (std::ostream&, const Point2D&);
	friend std::istream& operator >> (std::istream&, Point2D&);
};

const Point2D kInfPoint2D = Point2D(INF, INF);
const Point2D kNegInfPoint2D = Point2D(-INF, -INF);

#endif /*POINT2D_HPP_*/
