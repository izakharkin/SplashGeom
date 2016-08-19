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
#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

#include "point3D.hpp"
#include "vector3D.hpp"
#include "segment3D.hpp"
#include "shape3D.hpp"

class Cylinder: public Shape3D
{
public:
	Cylinder(double _radius, double _height, const Point3D& _center, const Vector3D& _rad_vec, const Vector3D& _direc_vec);
	Cylinder(Segment3D rad_seg, Segment3D direc_seg);

	void SetCenter(const Point3D&);
	void SetRadius(double);
	void SetHeight(double);

	Point3D GetCenter() const;
	double GetRadius() const;
	double GetHeight() const;

	double Volume() const;
	double SideArea() const;
	double SurfaceArea() const;

	void ScaleCylinder(double factor);

	bool Contains(const Point3D&) const;
	bool Boundary(const Point3D&) const;
	bool Intersect(const Segment3D&, vector<Point3D>&) const;
private:
	double radius;
	double height;
	Point3D center;
	Vector3D rad_vec;
	Vector3D direc_vec;
};

#endif /*CYLINDER_HPP_*/

