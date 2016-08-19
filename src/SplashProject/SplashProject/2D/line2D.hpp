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
#ifndef LINE2D_HPP_
#define LINE2D_HPP_

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

#include "point2D.hpp"
#include "vector2D.hpp"
#include "segment2D.hpp"
#include "ray2D.hpp"

class Line2D
{
public:
	Line2D();
	Line2D(const Ray2D&);
	Line2D(const Segment2D&);
	Line2D(const Point2D&, const Point2D&);
	Line2D(const Point2D& point, const Vector2D& direction);

	double PointIntoLine2D(const Point2D& point_to_insert_into_line) const;
	int Sign(const Point2D& point) const;
	Vector2D Direction() const;
	Vector2D NormalVec() const;

	Segment2D ToSegment() const;
	Ray2D ToRay() const;

	double Distance(const Point2D& point) const;
	double Distance(const Line2D& second_line) const; // !!! HERE ARE LINES IN 3D !!!

	bool Contains(const Point2D& point) const;

	// Intersection of two lines
	// ?params: second_line - the line with which we find intersection
	// ?return: returns Point2D(INF, INF) if there is no intersection,
	//          returns Point2D(-INF, -INF) if there it is the same line,
	//          else returns point of their intersection (in 2D)
	// ?complexity: O(1)
	Point2D GetIntersection(const Line2D& second_line) const;
	// Intersection of line and segment
	// ?params: segment - the segment with which we find intersection
	// ?return: returns Point2D(INF, INF) if there is no intersection,
	//          if this line contains segment, returns first point of segment,
	//          else returns point of their intersection (in 2D)
	// ?complexity: O(1)
	Point2D GetIntersection(const Segment2D& segment) const;
	// Intersection of line and segment
	// ?params: ray - the ray with which we find intersection
	// ?return: returns Point2D(INF, INF) if there is no intersection,
	//          if this line 'contains' ray, returns start point of ray,
	//          else returns point of their intersection (in 2D)
	// ?complexity: O(1)
	Point2D GetIntersection(const Ray2D& ray) const;

	bool HasIntersection(const Line2D& second_line) const;
	bool HasIntersection(const Segment2D& segment) const;
	bool HasIntersection(const Ray2D& ray) const;
private:
	double A;
	double B;
	double C;
};

#endif /*LINE2D_HPP_*/