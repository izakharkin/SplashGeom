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
/*
Circle::Circle(const Circle& second_circle)
: center_(second_circle.center_), little_haxis_(second_circle.little_haxis_), big_haxis_(second_circle.big_haxis_) {}

void Circle::operator = (const Circle& second_circle)
{

}

Circle::Circle(Circle&& second_circle)
{

}

void Circle::operator = (Circle&& second_circle)
{

}
*/
Circle::Circle(const Point2D& p1, const Point2D& p2, const Point2D& p3)
{
	Segment2D first_segment(p1, p2);
	Segment2D second_segment(p2, p3);
	Line2D first_perpendicular(first_segment.GetCenter(), first_segment.NormalVec());
	Line2D second_perpendicular(second_segment.GetCenter(), second_segment.NormalVec());
	this->center_ = first_perpendicular.GetIntersection(second_perpendicular);
	this->little_haxis_ = this->big_haxis_ = center_.l2_distance(p1);
}

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

Point2D Circle::GetLowestPoint() const
{
	return Point2D(this->center_ + Point2D(0, this->center_.y + this->little_haxis_));
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

vector<Point2D> Circle::GetIntersection(const Line2D&) const
{
	return vector<Point2D>();
}

vector<Point2D> Circle::GetIntersection(const Ray2D&) const
{
	return vector<Point2D>();
}

vector<Point2D> Circle::GetIntersection(const Segment2D&) const
{
	return vector<Point2D>();
}