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
#include "polygon.hpp"

Polygon::Polygon()
	: vertices_(0) {}

Polygon::Polygon(int n)
	: vertices_(n) {}

Polygon::Polygon(const Polygon& second_polygon)
{
	vertices_.resize(second_polygon.Size());
	std::copy(second_polygon.vertices_.begin(), second_polygon.vertices_.end(), vertices_.begin());
}

Polygon& Polygon::operator =(const Polygon& second_polygon)
{
	vertices_ = second_polygon.vertices_;
	return *this;
}

Polygon::Polygon(const vector<Point2D>& points)
{
	vertices_.resize(points.size());
	std::copy(points.begin(), points.end(), vertices_.begin());
}

Polygon& Polygon::operator =(const vector<Point2D>& points)
{
	std::copy(points.begin(), points.end(), vertices_.begin());
	return *this;
}

Polygon::Polygon(Polygon&& second_polygon)
{
	vertices_ = std::move(second_polygon.vertices_);
}

Polygon& Polygon::operator =(Polygon&& second_polygon)
{
	vertices_ = std::move(second_polygon.vertices_);
	return *this;
}

size_t Polygon::Size() const
{
	return vertices_.size();
}

double Polygon::Area() const 
{
	double area = 0;
	for (size_t i = 0; i < this->Size(); ++i) {
		size_t j = (i + 1) % this->Size();
		area += Vector2D(vertices_[i]).OrientedCCW(Vector2D(vertices_[j] - vertices_[i]));
	}
	return fabs(area / 2.0);
}

double Polygon::Perimeter() const
{
	double perimeter = 0;
	for (size_t i = 0; i < this->Size(); ++i) {
		size_t j = (i + 1) % this->Size();
		perimeter += Segment2D(vertices_[i], vertices_[j]).Length();
	}
	return perimeter;
}

bool Polygon::Contains(const Point2D& point) const
{
	int num_of_cross_sides = 0;
	Ray2D checking_ray(point, Vector2D(1, 0));
	bool is_on_border = false;
	for (size_t i = 0; i < this->Size() && !is_on_border; ++i) {
		int j = (i + 1) % this->Size();
		Segment2D cur_side(vertices_[i], vertices_[j]);
		if (cur_side.Contains(point)) {
			is_on_border = true;
			num_of_cross_sides = 1;
		} else if (checking_ray.HasIntersection(cur_side)) {
			num_of_cross_sides++;
		}
	}
	return num_of_cross_sides % 2 == 1;
}

bool Polygon::Boundary(const Point2D & point) const
{
	bool is_on_border = false;
	for (size_t i = 0; i < this->Size() && !is_on_border; ++i) {
		size_t j = (i + 1) % this->Size();
		Segment2D cur_side(vertices_[i], vertices_[j]);
		if (cur_side.Contains(point)) {
			is_on_border = true;
		}
	}
	return is_on_border;
}

vector<Point2D> Polygon::GetIntersection(const Line2D& line) const
{
	vector<Point2D> intersect_points;
	for (size_t i = 0; i < this->Size(); ++i) {
		size_t j = (i + 1) % this->Size();
		Segment2D cur_side(vertices_[i], vertices_[j]);
		Point2D cur_intersection = line.GetIntersection(cur_side);
		if (cur_intersection != kInfPoint2D) {
			intersect_points.push_back(cur_intersection);
		}
	}
	return intersect_points;
}

vector<Point2D> Polygon::GetIntersection(const Ray2D& ray) const
{
	vector<Point2D> intersect_points;
	for (size_t i = 0; i < this->Size(); ++i) {
		size_t j = (i + 1) % this->Size();
		Segment2D cur_side(vertices_[i], vertices_[j]);
		Point2D cur_intersection = ray.GetIntersection(cur_side);
		if (cur_intersection != kInfPoint2D) {
			intersect_points.push_back(cur_intersection);
		}
	}
	return intersect_points;
}

vector<Point2D> Polygon::GetIntersection(const Segment2D& segment) const
{
	vector<Point2D> intersect_points;
	for (size_t i = 0; i < this->Size(); ++i) {
		size_t j = (i + 1) % this->Size();
		Segment2D cur_side(vertices_[i], vertices_[j]);
		Point2D cur_intersection = segment.GetIntersection(cur_side);
		if (cur_intersection != kInfPoint2D) {
			intersect_points.push_back(cur_intersection);
		}
	}
	return intersect_points;
}