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
#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

#include "point2D.hpp"
#include "vector2D.hpp"
#include "line2D.hpp"
#include "segment2D.hpp"
#include "polygon.hpp"
#include "convex2D.hpp"

class Rectangle : public Convex2D
{
public:
	Rectangle();
	Rectangle(const vector<Point2D>& points);
	Rectangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, const Point2D& p4);

	double Area() const;
	bool Contains(const Point2D&) const;
	bool Boundary(const Point2D&) const;
	bool Intersect(const Segment2D&, Point2D&, Point2D&) const;

	Convex2D GetIntersectionalConvex2D(const Point2D& cur_point, const Line2D& halfplane) const;
};

Rectangle max_rect(Point2D(INF, INF), Point2D(-INF, INF), Point2D(INF, -INF), Point2D(-INF, -INF));

#endif /*RECTANGLE_HPP_*/