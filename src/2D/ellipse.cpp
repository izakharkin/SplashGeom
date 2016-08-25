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
#include "ellipse.hpp"

Ellipse::Ellipse()
	: center_(), big_haxis_(0.0), little_haxis_(0.0) {}

Ellipse::Ellipse(const Point2D& center, double a, double b)
	: center_(center), big_haxis_(b), little_haxis_(a) {}

double Ellipse::Area() const
{
	return M_PI * little_haxis_ * big_haxis_;
}

bool Ellipse::Contains(const Point2D& point) const
{
	return (pow(point.x, 2) / pow(big_haxis_, 2) + pow(point.y, 2) / pow(little_haxis_, 2) <= 1);
}

bool Ellipse::Boundary(const Point2D& point) const
{
	return (pow(point.x, 2) / pow(big_haxis_, 2) + pow(point.y, 2) / pow(little_haxis_, 2) == 1);
}

vector<Point2D> Ellipse::GetIntersection(const Line2D& line) const
{
	double k, b;
	double lA = line.GetA();
	double lB = line.GetB();
	double lC = line.GetC();
	if (lB == 0) {
		k = 0;
		b = 0;
	} else {
		k = -lA / lB;
		b = -lC / lB;
	}
	double a1 = pow(little_haxis_, 2);
	double a2 = pow(big_haxis_, 2);
	double a3 = 0;
	double a4 = -2 * pow(little_haxis_, 2) * center_.x;
	double a5 = -2 * pow(big_haxis_, 2) * center_.y;
	double a6 = pow(little_haxis_, 2) * pow(center_.x, 2) + pow(big_haxis_, 2) * pow(center_.y, 2) - 1;

	double A = a1 + a2 * pow(k, 2) + a3 * k;
	double B = 2 * k * b * a2 + a5 * k + a3 * b + a4;
	double C = a6 + a2 * pow(b, 2) + a5 * b;

	vector<double> roots(GetQuadraticSolution(A, B, C));
	vector<Point2D> intersect_points;
	for (auto x : roots) {
		double y = k * x + b;
		intersect_points.push_back(Point2D(x, y));
	}

	return intersect_points;
}

vector<Point2D> Ellipse::GetIntersection(const Ray2D& ray) const
{
	Line2D line(ray);
	vector<Point2D> intersect_points = this->GetIntersection(line);
	vector<Point2D> ray_inter_points;
	for (auto i : intersect_points) {
		if (ray.Contains(i)) {
			ray_inter_points.push_back(i);
		}
	}
	return ray_inter_points;
}

vector<Point2D> Ellipse::GetIntersection(const Segment2D& segment) const
{
	Line2D line(segment);
	vector<Point2D> intersect_points = this->GetIntersection(line);
	vector<Point2D> segment_inter_points;
	for (auto i : intersect_points) {
		if (segment.Contains(i)) {
			segment_inter_points.push_back(i);
		}
	}
	return segment_inter_points;
}