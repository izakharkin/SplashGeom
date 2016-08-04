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
#ifndef SEGMENT_HPP_
#define SEGMENT_HPP_

#include "splash_forward.hpp"
#include "splash_utils.hpp"

#include "point2D.hpp"
#include "vector2D.hpp"
#include "line2D.hpp"

class Segment2D
{
public:
	Point2D a;
	Point2D b;

	Segment2D();
	Segment2D(const Point2D& point_a, const Point2D& point_b);
	
	void Reversr();

	double Length() const;
	Point2D Center() const;
	bool Point2DInBox(const Point2D& point) const;

	Vector2D Dir() const;

	bool Contains(const Point2D& point) const;
	// Intersection of two segments
	// ?params: second_seg - the segment with which we find intersection
	// ?return: returns Point2D(INF, INF) if there is no intersection,
	//          if one segment intersects another not only with one point, returns some point of their 'intersection segment',
	//          else return point of their intersection
	Point2D Intersect(const Segment2D& second_seg) const;
	// Intersection of line and segment
	// ?params: segment - the segment with which we find intersection
	// ?return: returns Point2D(INF, INF) if there is no intersection,
	//          if this line contains segment, returns first point of segment,
	//          else returns point of their intersection (in 2D)
	// ?complexity: O(1)
	Point2D Intersect(const Line2D& line) const;
	// Intersection of segment and ray
	// ?params: ray - the ray with which we find intersection
	// ?return: returns Point2D(INF, INF) if there is no intersection,
	//          if ray contains this segment, returns first point of segment,
	//          if this segment contains pos_ of ray, returns pos_ of ray,
	//          else returns point of their intersection (in 2D)
	// ?complexity: O(1)
	Point2D Intersect(const Ray2D& ray) const;
};

#endif /*SEGMENT_HPP_*/