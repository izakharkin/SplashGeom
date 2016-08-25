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
#include "rectangle.hpp"

Rectangle::Rectangle()
	: Convex2D(4) {}

Rectangle::Rectangle(const vector<Point2D>& points)
	: Convex2D(points) {}

Rectangle::Rectangle(const Point2D& p1, const Point2D& p2, const Point2D& p3, const Point2D& p4)
	: Convex2D(vector<Point2D>{p1, p2, p3, p4}) {}

double Rectangle::Area() const
{
	return Convex2D::Area();
}

double Rectangle::Perimeter() const
{
	return Convex2D::Perimeter();
}

bool Rectangle::Contains(const Point2D& point) const
{
	return Convex2D::Contains(point);
}

bool Rectangle::Boundary(const Point2D & point) const
{
	return Convex2D::Boundary(point);
}

Convex2D Rectangle::GetIntersectionalConvex2D(const Point2D& cur_point, const Line2D& halfplane) const
{
	vector<Point2D> convex_points;
	Segment2D cur_side;
	Point2D intersection_point;
	for (int i = 0, sz = vertices_.size(); i < sz; ++i) {
		int j = (i + 1) % sz;
		cur_side = Segment2D(vertices_[i], vertices_[j]);
		intersection_point = halfplane.GetIntersection(cur_side);
		if (intersection_point != kInfPoint2D)
			convex_points.push_back(intersection_point);
		if (halfplane.Sign(cur_point) == halfplane.Sign(vertices_[i]))
			convex_points.push_back(vertices_[i]);
	}
	Convex2D result_polygon(MakeConvexHullJarvis(convex_points));
	return result_polygon;
}

vector<Point2D> Rectangle::GetIntersection(const Line2D& line) const
{
	return Convex2D::GetIntersection(line);
}

vector<Point2D> Rectangle::GetIntersection(const Ray2D& ray) const
{
	return Convex2D::GetIntersection(ray);
}

vector<Point2D> Rectangle::GetIntersection(const Segment2D& segment) const
{
	return Convex2D::GetIntersection(segment);
}