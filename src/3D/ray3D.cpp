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
#include "ray3D.hpp"

Ray3D::Ray3D()
	: pos_(), dir_() {}

Ray3D::Ray3D(const Point3D& pos, const Vector3D& dir)
	: pos_(pos), dir_(dir) {}

Vector3D Ray3D::Direction() const
{
	return dir_;
}

Vector3D Ray3D::NormalVec() const
{
	return dir_.Ortopair();
}

double Ray3D::Distance(const Point3D& point) const
{
	double dot_product = dir_.Dot(Vector3D(pos_, point));
	double distance;
	if (fabs(dot_product) < EPS) {
		distance = pos_.l2_distance(point);
	} else {
		distance = Line3D(*this).Distance(point);
	}
	return distance;
}

bool Ray3D::Contains(const Point3D& point) const
{
	double dot_product = dir_.Dot(Vector3D(pos_, point));
	return (dot_product >= EPS && Line3D(*this).Contains(point));
}

Point3D Ray3D::GetIntersection(const Line3D& second_line) const
{
	Line3D this_line(*this);
	Point3D intersect_point = this_line.GetIntersection(second_line);
	if (intersect_point != Point3D(INF, INF, INF) && !this->Contains(intersect_point)) {
		intersect_point = Point3D(INF, INF, INF);
	}
	return intersect_point;
}

Point3D Ray3D::GetIntersection(const Ray3D& second_ray) const
{
	Line3D this_line(*this);
	Line3D second_line(second_ray);
	Point3D intersect_point = this_line.GetIntersection(second_line);
	
	if (intersect_point != Point3D(INF, INF, INF) && (!this->Contains(intersect_point) || !second_ray.Contains(intersect_point)))
		intersect_point = Point3D(INF, INF, INF);

	return intersect_point;
}

Point3D Ray3D::GetIntersection(const Segment3D& segment) const
{
	Line3D this_line(*this);
	Line3D second_line(segment);
	Point3D intersect_point = this_line.GetIntersection(second_line);
	
	if (intersect_point != Point3D(INF, INF, INF) && (!this->Contains(intersect_point) || !segment.Contains(intersect_point)))
		intersect_point = Point3D(INF, INF, INF);
	
	return intersect_point;
}

bool Ray3D::HasIntersection(const Line3D& line) const
{
	return line.HasIntersection(*this);
}

bool Ray3D::HasIntersection(const Ray3D& second_ray) const
{
	return this->GetIntersection(second_ray) != Point3D(INF, INF, INF);
}

bool Ray3D::HasIntersection(const Segment3D& segment) const
{
	return this->GetIntersection(segment) != Point3D(INF, INF, INF);
}