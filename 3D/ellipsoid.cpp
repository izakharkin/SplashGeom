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
#include "ellipsoid.hpp"

Ellipsoid::Ellipsoid(const Point3D& center, double a, double b, double c) 
	: center_(center), ax1_(a), ax2_(b), ax3_(c) {}


void Ellipsoid::SetCenter(const Point3D& center) 
{
	center_ = center;
}

Point3D Ellipsoid::GetCenter() const 
{
	return center_;
}

double Ellipsoid::Volume() const 
{
	return (4 / 3) * ax1_ * ax2_ * ax3_ * M_PI;
}

double Ellipsoid::SurfaceArea() const 
{
    double p = 1.6075;
    return 4 * M_PI * pow(((pow(ax1_,p)*pow(ax2_,p)+pow(ax1_, p)*pow(ax3_, p)+pow(ax2_,p)*pow(ax3_,p))/3), (1/p));
}

bool Ellipsoid::Contains(const Point3D& point) const
{
	// Sinse an ellipsoid is a spherical object
    return this->Boundary(point);
}

bool Ellipsoid::Boundary(const Point3D& point) const
{
    return fabs(point.x * point.x / ax1_ / ax1_ + point.y * point.y / ax2_ / ax2_ + point.z * point.z / ax3_ / ax3_ - 1) < EPS;
}
