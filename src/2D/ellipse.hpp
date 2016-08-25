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
#ifndef ELLIPSE_HPP_
#define ELLIPSE_HPP_

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

#include "point2D.hpp"
#include "segment2D.hpp"
#include "shape2D.hpp"

class Ellipse : public Shape2D
{
public:
	explicit Ellipse();
	explicit Ellipse(const Point2D& center, double big_haxis, double little_haxis);

	void SetLittleAx(double new_value);
	void SetBigAx(double new_value);
	void SetCenter(const Point2D& new_point);

	double GetLittleAx() const;
	double GetBigAx() const;
	Point2D GetCenter() const;

	double Area() const;
	bool Length() const;

	bool Contains(const Point2D& point) const;
	bool Boundary(const Point2D& point) const;
	
	virtual vector<Point2D> GetIntersection(const Line2D& line) const override;
	virtual vector<Point2D> GetIntersection(const Ray2D& ray) const override;
	virtual vector<Point2D> GetIntersection(const Segment2D& segment) const override;
protected:
	Point2D center_;
	double big_haxis_;
	double little_haxis_;
};

#endif /*ELLIPSE_HPP_*/