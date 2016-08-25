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
#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

#include "convex2D.hpp"

class Triangle : public Convex2D
{
public:
	explicit Triangle();
	explicit Triangle(const vector<Point2D>& points);
	explicit Triangle(const Point2D& a, const Point2D& b, const Point2D& c);

	double GetSideA() const;
	double GetSideB() const;
	double GetSideC() const;

	double Area() const;
	double Perimeter() const;

	bool Contains(const Point2D& point) const;
	bool Boundary(const Point2D& point) const;

	virtual vector<Point2D> GetIntersection(const Line2D&) const override;
	virtual vector<Point2D> GetIntersection(const Ray2D&) const override;
	virtual vector<Point2D> GetIntersection(const Segment2D&) const override;
};

#endif /*TRIANGLE_HPP_*/