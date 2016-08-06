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
#ifndef RAY_HPP_
#define RAY_HPP_

#include "splash_forward.hpp"
#include "splash_utils.hpp"

#include "point2D.hpp"
#include "vector2D.hpp"
#include "segment2D.hpp"
#include "line2D.hpp"

class Ray2D
{
public:
	Point2D pos_;
	Vector2D dir_;

	Ray2D();
	Ray2D(const Point2D&, const Vector2D&);

	Vector2D Direction() const;
	Vector2D NormalVec() const;

	double Distance(const Point2D&) const;
	double Distance(const Ray2D&) const; // !!! HERE ARE RAYS IN 3D !!!

	bool Contains(const Point2D&) const;

	// Intersection of ray and line
	// ?params: second_line - the line with which we find intersection
	// ?return: returns Point2D(INF, INF) if there is no intersection,
	//          if line contains this ray, returns pos_ point of ray
	//          else returns point of their intersection (in 2D)
	// ?complexity: O(1)
	Point2D GetIntersection(const Line2D& second_line) const;
	// Intersection of two rays
	// ?params: second_ray - the ray with which we find intersection
	// ?return: returns Point2D(INF, INF) if there is no intersection,
	//          returns pos_ point of ray, that is contained in other ray, if those ray 'contains' that ray,
	//          else returns point of their intersection (in 2D)
	// ?complexity: O(1)
	Point2D GetIntersection(const Ray2D& second_ray) const;
	// Intersection of ray and segment
	// ?params: segment - the segment with which we find intersection
	// ?return: returns Point2D(INF, INF) if there is no intersection,
	//          if ray contains segment, returns first point of segment,
	//          if segment contains pos_ of this ray, returns pos_ of this ray,
	//          else returns point of their intersection (in 2D)
	// ?complexity: O(1)
	Point2D GetIntersection(const Segment2D& segment) const;

	bool HasIntersection(const Line2D& line) const;
	bool HasIntersection(const Ray2D& second_ray) const;
	bool HasIntersection(const Segment2D& segment) const;
};

#endif /*RAY_HPP_*/