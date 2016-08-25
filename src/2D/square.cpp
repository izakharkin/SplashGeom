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
#include "square.hpp"

Square::Square()
	: Convex2D() {}

Square::Square(const vector<Point2D>& points)
	: Convex2D(points) {}

Square::Square(const Point2D& p1, const Point2D& p2, const Point2D& p3, const Point2D& p4)
	: Convex2D(vector<Point2D>{p1, p2, p3, p4}) {}

double Square::Area() const
{
	return Convex2D::Area();
}

double Square::Perimeter() const
{
	return Convex2D::Perimeter();
}

bool Square::Contains(const Point2D& point) const
{
	return Convex2D::Contains(point);
}

bool Square::Boundary(const Point2D & point) const
{
	return Convex2D::Boundary(point);
}

vector<Point2D> Square::GetIntersection(const Line2D& line) const
{
	return Convex2D::GetIntersection(line);
}

vector<Point2D> Square::GetIntersection(const Ray2D& ray) const
{
	return Convex2D::GetIntersection(ray);
}

vector<Point2D> Square::GetIntersection(const Segment2D& segment) const
{
	return Convex2D::GetIntersection(segment);
}