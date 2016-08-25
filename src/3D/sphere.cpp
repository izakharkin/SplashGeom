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
#include "sphere.hpp"

Sphere::Sphere(const Point3D& center, double radius)
	: Ellipsoid(center, radius, radius, radius) {}

void Sphere::SetCenter(const Point3D& center)
{
	center_ = center;
}

Point3D Sphere::GetCenter() const
{
	return center_;
}

double Sphere::Volume() const
{
	return Ellipsoid::Volume();
}

double Sphere::SurfaceArea() const
{
	return Ellipsoid::SurfaceArea();
}

bool Sphere::Contains(const Point3D& point) const
{
	return Ellipsoid::Contains(point);
}

bool Sphere::Boundary(const Point3D& point) const
{
	return (point.l2_distance(center_) == ax1_);
}

vector<Point3D> Sphere::GetIntersection(const Line3D& line) const
{
	return vector<Point3D>();
}

vector<Point3D> Sphere::GetIntersection(const Ray3D& ray) const
{
	return vector<Point3D>();
}

vector<Point3D> Sphere::GetIntersection(const Segment3D& segment) const
{
	return vector<Point3D>();
}
