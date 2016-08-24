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
#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "splash_forward.hpp"
#include "splash_utils.hpp"

#include "convex2D.hpp"

class Square : public Convex2D
{
public:
	Square();
	Square(const vector<Point2D>& points);
	Square(const Point2D& p1, const Point2D& p2, const Point2D& p3, const Point2D& p4);

	double Area() const;
	bool Contains(const Point2D&) const;
	bool Boundary(const Point2D&) const;

	virtual vector<Point2D> GetIntersection(const Line2D&) const override;
	virtual vector<Point2D> GetIntersection(const Ray2D&) const override;
	virtual vector<Point2D> GetIntersection(const Segment2D&) const override;
};

const Rectangle kMaxSquare = Rectangle(Point2D(INF, INF), Point2D(-INF, INF), Point2D(-INF, -INF), Point2D(INF, -INF));

#endif /*SQUARE_HPP*/
