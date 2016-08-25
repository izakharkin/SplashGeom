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
#ifndef ELLIPSOID_HPP_
#define ELLIPSOID_HPP_

#include "splash_forward.hpp"
#include "splash_utils.hpp"

#include "point3D.hpp"
#include "vector3D.hpp"
#include "segment3D.hpp"
#include "shape3D.hpp"

class Ellipsoid : public Shape3D
{
public:
	Ellipsoid();
	Ellipsoid(const Point3D& center, double a, double b, double c);

	void SetCenter(const Point3D& new_center);

	Point3D GetCenter() const;
	double GetRadius() const;

	double SurfaceArea() const override;
	double Volume() const override;

	bool Contains(const Point3D& point) const override;
	bool Boundary(const Point3D& point) const override;
    
protected:
	Point3D center_;
	double ax1_;
	double ax2_;
	double ax3_;
};

#endif /*ELLIPSOID_HPP_*/
