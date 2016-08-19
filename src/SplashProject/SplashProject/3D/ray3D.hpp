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
#ifndef RAY3D_HPP_
#define RAY3D_HPP_

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

#include "point3D.hpp"
#include "vector3D.hpp"
#include "line3D.hpp"
#include "segment3D.hpp"

class Ray3D
{
public:
	Point3D pos_;
	Vector3D dir_;

	Ray3D();
	Ray3D(const Point3D&, const Vector3D&);

	Vector3D Direction() const;
	Vector3D NormalVec() const;

	double Distance(const Point3D&) const;
	double Distance(const Ray3D&) const; // !!! HERE ARE RAYS IN 3D !!!

	bool Contains(const Point3D&) const;

	// Intersection of ray and line
	// ?params: second_line - the line with which we find intersection
	// ?return: returns Point3D(INF, INF) if there is no intersection,
	//          if line contains this ray, returns pos_ point of ray
	//          else returns point of their intersection (in 3D)
	// ?complexity: O(1)
	Point3D GetIntersection(const Line3D& second_line) const;
	// Intersection of two rays
	// ?params: second_ray - the ray with which we find intersection
	// ?return: returns Point3D(INF, INF) if there is no intersection,
	//          returns pos_ point of ray, that is contained in other ray, if those ray 'contains' that ray,
	//          else returns point of their intersection (in 3D)
	// ?complexity: O(1)
	Point3D GetIntersection(const Ray3D& second_ray) const;
	// Intersection of ray and segment
	// ?params: segment - the segment with which we find intersection
	// ?return: returns Point3D(INF, INF) if there is no intersection,
	//          if ray contains segment, returns first point of segment,
	//          if segment contains pos_ of this ray, returns pos_ of this ray,
	//          else returns point of their intersection (in 3D)
	// ?complexity: O(1)
	Point3D GetIntersection(const Segment3D& segment) const;

	bool HasIntersection(const Line3D& line) const;
	bool HasIntersection(const Ray3D& second_ray) const;
	bool HasIntersection(const Segment3D& segment) const;
};

#endif /*RAY3D_HPP_*/