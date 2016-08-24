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
#include "triangle.hpp"

Triangle::Triangle()
	: Convex2D() {}

Triangle::Triangle(const Point2D& a, const Point2D& b, const Point2D& c)
	: Convex2D({ a, b, c }) {}

Triangle::Triangle(const vector<Point2D>& points)
	: Convex2D(points) {}

double Triangle::GetSideA() const
{
	return vertices_[0].l2_distance(vertices_[1]);
}

double Triangle::GetSideB() const
{
	return vertices_[1].l2_distance(vertices_[2]);
}

double Triangle::GetSideC() const
{
	return vertices_[2].l2_distance(vertices_[0]);
}

double Triangle::Area() const
{
	double half_perimeter = (GetSideA() + GetSideB() + GetSideC()) * 0.5;
	return sqrt(half_perimeter * (half_perimeter - GetSideA()) * (half_perimeter - GetSideB()) * (half_perimeter - GetSideC()));
}

bool Triangle::Contains(const Point2D& point) const
{
	int num_of_vertices = vertices_.size();
	if (num_of_vertices < 3) {
		//cerr << "Triangle is \"empty\"!";
		return false;
	}
	double sign;
	bool contains = true;
	for (int i = 0; i < num_of_vertices && contains; ++i) {
		int j = (i + 1) % num_of_vertices;
		if (Vector2D(point, vertices_[i]).Norm() == 0) {
			contains = true;
			break;
		}
		if (i == 0) {
			sign = sgn(Vector2D(point, vertices_[i]).OrientedCCW(Vector2D(vertices_[i], vertices_[j])));
		} else if (sgn(Vector2D(point, vertices_[i]).OrientedCCW(Vector2D(vertices_[i], vertices_[j]))) != sign &&
			       sgn(Vector2D(point, vertices_[i]).OrientedCCW(Vector2D(vertices_[i], vertices_[j]))) != 0) {
			contains = false;
		}
	}
	return contains;
}

bool Triangle::Boundary(const Point2D& point) const
{
	return Convex2D::Boundary(point);
}