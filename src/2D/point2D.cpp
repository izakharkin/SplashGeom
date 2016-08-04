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
#include "point2D.hpp"

Point2D::Point2D()
	: x(0.0), y(0.0) {}

Point2D::Point2D(double _x, double _y)
	: x(_x), y(_y) {}

std::ostream& operator << (std::ostream& o, const Point2D& p)
{
	o << p.x << ' ' << p.y;
	return o;
}

std::istream& operator >> (std::istream& in, Point2D& new_point)
{
	in >> new_point.x >> new_point.y;
	return in;
}

bool Point2D::operator == (const Point2D& b) const
{
	return this->x == b.x && this->y == b.y;
}

bool Point2D::operator != (const Point2D& b) const
{
	return !(*this == b);
}

bool Point2D::operator < (const Point2D& b) const
{
	return this->x < b.x - EPS || fabs(this->x - b.x) < EPS &&  this->y < b.y - EPS;
}

Point2D Point2D::operator + (const Point2D& b) const
{
	return Point2D(this->x + b.x, this->y + b.y);
}

Point2D Point2D::operator - (const Point2D& b) const
{
	return Point2D(this->x - b.x, this->y - b.y);
}

Point2D Point2D::operator * (double num) const
{
	return Point2D(this->x * num, this->y * num);
}

Point2D Point2D::operator / (double num) const
{
	return Point2D(this->x / num, this->y / num);
}

double Point2D::l1_distance(const Point2D& b) const
{
	return fabs(this->x - b.x) + fabs(this->y - b.y);
}

double Point2D::l2_distance(const Point2D& b) const
{
	return sqrt((this->x - b.x) * (this->x - b.x) + (this->y - b.y) * (this->y - b.y));
}