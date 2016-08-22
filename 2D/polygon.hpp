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
#ifndef POLYGON_HPP_
#define POLYGON_HPP_

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

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

	Polygon(const Polygon& second_polygon);
	void operator =(const Polygon& second_polygon);

	Polygon(Polygon&& second_polygon);
	void operator =(Polygon&& second_polygon);

	Polygon(const vector<Point2D>& points);
	void operator =(const vector<Point2D>& points);

	int Size() const;

	virtual double Area() const;
	virtual bool Contains(const Point2D& point) const;
	virtual bool Boundary(const Point2D& point) const;
	
	virtual vector<Point2D> GetIntersection(const Line2D&) const override;
	virtual vector<Point2D> GetIntersection(const Ray2D&) const override;
	virtual vector<Point2D> GetIntersection(const Segment2D& segment) const override;

	Polygon GetIntersection(const Polygon& second_polygon) const;
protected:
	vector<Point2D> vertices_;
};

#endif /*POLYGON_HPP_*/