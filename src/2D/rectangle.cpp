// Splash (c) - open-source C++ library for geometry and linear algebra
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
	along with Splash.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "rectangle.hpp"

Rectangle::Rectangle()
	: Convex2D(4) {}

Rectangle::Rectangle(const vector<Point2D>& points)
	: Convex2D(points) {}

double Rectangle::Area() const
{
	return Segment2D(vertices_[0], vertices_[1]).Length() * Segment2D(vertices_[2], vertices_[3]).Length();
}

bool Rectangle::Contains(const Point2D& point) const
{
	return Convex2D::Contains(point);
}

bool Rectangle::Boundary(const Point2D & point) const
{
	return Polygon::Boundary(point);
}

bool Rectangle::Intersect(const Segment2D& seg, Point2D& p1, Point2D& p2) const
{
	return 0;
}

Convex2D Rectangle::GetIntersectionalConvex2D(const Point2D& cur_point, const Line2D& halfplane) const
{
	vector<Point2D> conv_points;

	Segment2D cur_side;
	for (int i = 0, sz = vertices_.size(); i < sz; ++i) {
		int j = (i + 1) % sz;
		cur_side = Segment2D(vertices_[i], vertices_[j]);
		Point2D intersection_point = halfplane.GetIntersection(cur_side);
		if (intersection_point != Point2D(INF, INF))
			conv_points.push_back(cur_side.GetIntersection(halfplane));
		if (halfplane.Sign(cur_point) == halfplane.Sign(vertices_[i]))
			conv_points.push_back(vertices_[i]);
	}

	return Convex2D().MakeConvexHullJarvis(conv_points);
}