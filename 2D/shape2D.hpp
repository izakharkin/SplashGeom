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
#ifndef SHAPE2D_HPP_
#define SHAPE2D_HPP_

#include "splash_forward.hpp"
#include "splash_utils.hpp"

class Shape2D
{
public:
	virtual double Area() const = 0;
	virtual double Perimeter() const = 0;

	virtual bool Contains(const Point2D&) const = 0;
	virtual bool Boundary(const Point2D&) const = 0;

	virtual vector<Point2D> GetIntersection(const Line2D&) const = 0;
	virtual vector<Point2D> GetIntersection(const Ray2D&) const = 0;
	virtual vector<Point2D> GetIntersection(const Segment2D&) const = 0;

	virtual ~Shape2D() {}
};

#endif /*SHAPE2D_HPP_*/
