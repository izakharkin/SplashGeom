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
#include "cylinder.hpp"

Cylinder::Cylinder(double _radius, double _height, const Point3D& _center, const Vector3D& _rad_vec, const Vector3D& _dir_vec)
	: radius(_radius), height(_height), center(_center), 
		rad_vec(make_shared<Vector3D>(_rad_vec)), 
		dir_vec(make_shared<Vector3D>(_dir_vec)) {}

void Cylinder::SetCenter(const Point3D& _center)
{
	center = _center;
}

void Cylinder::SetRadius(double _radius)
{
	radius = _radius;
}

void Cylinder::SetHeight(double _height)
{
	height = _height;
}

Point3D Cylinder::GetCenter() const
{
	return center;
}

double Cylinder::GetRadius() const
{
	return radius;
}

double Cylinder::GetHeight() const
{
	return height;
}

double Cylinder::Volume() const
{
	return radius * radius * height * M_PI;
}

double Cylinder::SideSurfaceArea() const
{
	return 2 * radius  * M_PI * height;
}

double Cylinder::SurfaceArea() const
{
	return 2 * radius * M_PI * (height + radius);
}

void Cylinder::ScaleCylinder(double factor)
{
	radius *= factor;
	height *= factor;
}

bool Cylinder::Contains(const Point3D& point) const
{
	return 0;
}

bool Cylinder::Boundary(const Point3D& point) const
{
	return 0;
}

vector<Point3D> Cylinder::GetIntersection(const Line3D& line) const
{
	return vector<Point3D>();
}

vector<Point3D> Cylinder::GetIntersection(const Ray3D& ray) const
{
	return vector<Point3D>();
}

vector<Point3D> Cylinder::GetIntersection(const Segment3D& segment) const
{
	return vector<Point3D>();
}
