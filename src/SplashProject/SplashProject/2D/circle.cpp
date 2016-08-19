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
#include "circle.hpp"

Circle::Circle()
	: Ellipse() {}

Circle::Circle(const Point2D& center, double radius)
	: Ellipse(center, radius, radius) {}

void Circle::SetCenter(const Point2D& new_center)
{
	center_ = new_center;
}
void Circle::SetRadius(double new_radius)
{
	little_haxis_ = big_haxis_ = new_radius;
}

Point2D Circle::GetCenter() const
{
	return center_;
}

double Circle::GetRadius() const
{
	return little_haxis_;
}

double Circle::Area() const
{
	return Ellipse::Area();
}

bool Circle::Contains(const Point2D& point) const
{
	return this->center_.l2_distance(point) <= little_haxis_;
}

bool Circle::Boundary(const Point2D& point) const
{
	return this->center_.l2_distance(point) == little_haxis_;
}

bool Circle::Intersect(const Segment2D& segment, Point2D& intersect_1, Point2D& intersect_2) const
{
	return 0;
}