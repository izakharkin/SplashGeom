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

	bool Contains(const Point3D&) const;

	Point3D GetIntersection(const Line3D& second_line) const;
	Point3D GetIntersection(const Ray3D& second_ray) const;
	Point3D GetIntersection(const Segment3D& segment) const;

	bool HasIntersection(const Line3D& line) const;
	bool HasIntersection(const Ray3D& second_ray) const;
	bool HasIntersection(const Segment3D& segment) const;
};

#endif /*RAY3D_HPP_*/
