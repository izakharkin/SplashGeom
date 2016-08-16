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
#include "cylinder.hpp"

Cylinder::Cylinder(double _radius, double _height, const Point3D& _center, const Vector3D& _rad_vec, const Vector3D& _direc_vec)
{
	radius = _radius;
	height = _height;
	center = _center;
	rad_vec = _rad_vec;
	direc_vec = _direc_vec;
}

//Cylinder::Cylinder(Segment3D rad_seg, Segment3D direc_seg)
//{
//    radius = 0.5 * rad_seg.length();
//    center = Point3D(((direc_seg.a).x + (direc_seg.b).x)/2, ((direc_seg.a).y + (direc_seg.b).y)/2, ((direc_seg.a).z + (direc_seg.b).z)/2);
//    rad_vec = rad_seg.Dir();
//    direc_vec = direc_seg.Dir();
//    height = direc_seg.length() * sin(direc_vec.AbcAngle(rad_vec));
//}

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

double Cylinder::SideArea() const
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

bool Cylinder::Intersect(const Segment3D& seg, vector<Point3D>& intersect_points) const
{
	return 0;
}