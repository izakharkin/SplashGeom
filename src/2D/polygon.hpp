// Splash (c) - open-source C++ library for geometry and linear algebra
// Copyright (c) 2016, Ilya Zakharkin, Elena Kirilenko and Nadezhda Kasimova.
// All rights reserved.
/*
	This file is part of Splash.

	Splash is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Foobar is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef POLYGON_HPP_
#define POLYGON_HPP_

#include "splash_forward.hpp"
#include "splash_utils.hpp"
#include "point2D.hpp"
#include "vector2D.hpp"
#include "line2D.hpp"
#include "segment2D.hpp"
#include "shape2D.hpp"

class Polygon : public Shape2D
{
public:
	Polygon();
	Polygon(int n);
	Polygon(const vector<Point2D>& points);
	void operator =(const vector<Point2D>& points);

	double Area() const;
	bool Contains(const Point2D&) const;
	bool Boundary(const Point2D&) const;
	bool Intersect(const Segment2D&, Point2D&, Point2D&) const;
protected:
	vector<Point2D> vertices_;
};

#endif /*POLYGON_HPP_*/