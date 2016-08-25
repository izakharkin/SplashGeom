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
#ifndef SHAPE3D_HPP_
#define SHAPE3D_HPP_

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

class Shape3D
{
public:
	virtual double Volume() const = 0;
	virtual double SurfaceArea() const = 0;

	virtual bool Contains(const Point3D&) const = 0;
	virtual bool Boundary(const Point3D&) const = 0;

	virtual vector<Point3D> GetIntersection(const Line3D&) const = 0;
	virtual vector<Point3D> GetIntersection(const Ray3D&) const = 0;
	virtual vector<Point3D> GetIntersection(const Segment3D&) const = 0;

	virtual ~Shape3D() {}
};

#endif /*SHAPE3D_HPP_*/
