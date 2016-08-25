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
#ifndef Line3D_HPP_
#define Line3D_HPP_

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

#include "point3D.hpp"
#include "vector3D.hpp"
#include "segment3D.hpp"
#include "ray3D.hpp"

class Line3D
{
public:
	Line3D();
	Line3D(const Ray3D&);
	Line3D(const Segment3D&);
	Line3D(const Point3D&, const Point3D&);
	Line3D(const Point3D& point, const Vector3D& direction);

	Vector3D Direction() const;
	Vector3D NormalVec() const;
	Vector3D GetVec() const;

	double Distance(const Point3D& point) const;
	double Distance(const Line3D& second_line) const; // !!! HERE ARE LINES IN 3D !!!

	bool Contains(const Point3D& point) const;

	Point3D GetPoint() const;

	Point3D GetIntersection(const Line3D& second_line) const;
	Point3D GetIntersection(const Segment3D& segment) const;
	Point3D GetIntersection(const Ray3D& ray) const;

	bool HasIntersection(const Line3D& second_line) const;
	bool HasIntersection(const Segment3D& segment) const;
	bool HasIntersection(const Ray3D& ray) const;
private:
	//We will set line as the point and vector
	Point3D M;
	Vector3D vect_direction;
};

#endif /*Line3D_HPP_*/