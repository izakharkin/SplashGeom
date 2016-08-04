// Splash (c) - open-source C++ library for geometry and linear algebra
// Copyright (c) 2016, Ilya Zakharkin, Elena Kirilenko and Nadezhda Kasimova.
// All rights reserved.
/*
	This file is part of Splash.

	Splash is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Foobar is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef ELLIPSOID_HPP_
#define ELLIPSOID_HPP_

#include "splash_forward.hpp"
#include "splash_utils.hpp"

class Ellipsoid : public Shape3D
{
public:
	Ellipsoid();
	Ellipsoid(const Point3D& center, double, double, double);

	void SetCenter(const Point3D&);

	Point3D GetCenter() const;
	double GetRadius() const;

	double Area() const;
	bool Contains(const Point3D&) const;
	bool Boundary(const Point3D&) const;
	bool Intersect(const Segment3D&, Point3D&, Point3D&) const;
private:
	Point3D center_;
	double ax1_;
	double ax2_;
	double ax3_;
};


#endif /*ELLIPSOID_HPP_*/