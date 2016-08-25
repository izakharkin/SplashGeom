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
	Cylinder();
	Cylinder(Segment3D rad_seg, Segment3D dir_seg);
	Cylinder(double _radius, double _height, const Point3D& _center, const Vector3D& _rad_vec, const Vector3D& _direc_vec);

	void SetCenter(const Point3D&);
	void SetRadius(double);
	void SetHeight(double);

	Point3D GetCenter() const;
	double GetRadius() const;
	double GetHeight() const;

	double Volume() const;
	double SideSurfaceArea() const;
	double SurfaceArea() const;

	void ScaleCylinder(double factor);

	bool Contains(const Point3D& point) const;
	bool Boundary(const Point3D& point) const;
	
	virtual vector<Point3D> GetIntersection(const Line3D& line) const override;
	virtual vector<Point3D> GetIntersection(const Ray3D& ray) const override;
	virtual vector<Point3D> GetIntersection(const Segment3D& segment) const override;
private:
	double radius;
	double height;
	Point3D center;
	shared_ptr<Vector3D> rad_vec;
	shared_ptr<Vector3D> dir_vec;
};

#endif /*CYLINDER_HPP_*/

