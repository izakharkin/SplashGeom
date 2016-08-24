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
#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "splash_forward.hpp"
#include "splash_utils.hpp"

#include "ellipsoid.hpp"

class Sphere : public Ellipsoid
{
public:
	Sphere();
	Sphere(const Point3D& center, double radius);

	void SetCenter(const Point3D&);
	void SetRadius(double);

	Point3D GetCenter() const;
	double GetRadius() const;

	double SurfaceArea() const;
	double Volume() const;

	bool Contains(const Point3D&) const;
	bool Boundary(const Point3D&) const;
	
	virtual vector<Point3D> GetIntersection(const Line3D& line) const override;
	virtual vector<Point3D> GetIntersection(const Ray3D& ray) const override;
	virtual vector<Point3D> GetIntersection(const Segment3D& segment) const override;
};


#endif /*SPHERE_HPP_*/
