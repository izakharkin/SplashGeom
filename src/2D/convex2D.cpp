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
#include "convex2D.hpp"

Convex2D::Convex2D()
	: Polygon() {}

Convex2D::Convex2D(int n)
	: Polygon(n) {}

Convex2D::Convex2D(const vector<Point2D>& points)
	: Polygon(points) {}

void Convex2D::makeConvexHull(const vector<Point2D>& points)
{
	this->vertices_ = points;


}

double Convex2D::Area() const
{
	return Polygon::Area();
}
/*
// Preparata, Shaymos - binary search and localization
// tested: informatics.mccme.ru: OK
// complexity: O(N)
bool Convex::Contains(const Point2D& point) const
{
// center of mass
Point2D central_point = (vertices_[0] + vertices_[1] + vertices_[2]) / 3.0;
int num_of_vertices = vertices_.size();
bool is_inside = false;
// detect the right klin (angle), where our Point2D is situated
for (int i = 0, j; i < num_of_vertices; ++i)
{
j = (i + 1) % num_of_vertices;
Vector2D cpoint_point(central_point, point);
if (cpoint_point.OrientedCCW(Vector2D(central_point, vertices_[j])) >= 0 && cpoint_point.OrientedCCW(Vector2D(central_point, vertices_[i])) <= 0) // we found the right place for our Point2D
{
Vector2D point_pi(point, vertices_[i]);
Vector2D pi_pj(vertices_[i], vertices_[j]);
if (point_pi.OrientedCCW(pi_pj) > 0)
is_inside = true;
else
is_inside = false;
break;
}
}

return is_inside;
}
*/
// Localization of Point2D in convex (star) polynom
// Preparata, Shaymos - localization (with bynary search)
// tested: informatics.mccme.ru: OK, acmp.ru: OK
// complexity: O(logN)
bool Convex2D::Contains(const Point2D& point) const
{
	// center of mass
	Point2D central_point = (vertices_[0] + vertices_[1] + vertices_[2]) / 3.0;
	int num_of_vertices = vertices_.size();
	bool contains = false;

	// detect the right klin (angle), where our Point2D is situated
	int r = num_of_vertices - 1, l = 0;
	Vector2D cpoint_point(central_point, point);
	Vector2D cpoint_p0(central_point, vertices_[0]);
	while (r - l > 0)
	{
		int i = (l + r) >> 1;
		if (cpoint_p0.PolarAngle(cpoint_point) > cpoint_p0.PolarAngle(Vector2D(central_point, vertices_[i])))
		{
			int j = (i + 1) % num_of_vertices;
			if (cpoint_p0.PolarAngle(cpoint_point) < cpoint_p0.PolarAngle(Vector2D(central_point, vertices_[j])))
			{
				Vector2D point_pi(point, vertices_[i]);
				Vector2D pi_pj(vertices_[i], vertices_[j]);
				contains = (point_pi.OrientedCCW(pi_pj) >= 0);
				break;
			}
			else if (cpoint_p0.PolarAngle(cpoint_point) == cpoint_p0.PolarAngle(Vector2D(central_point, vertices_[j])))
			{
				contains = (central_point.l2_distance(vertices_[j]) >= central_point.l2_distance(point));
				break;
			}
			else /*if (cpoint_p0.PolarAngle(cpoint_point) > cpoint_p0.PolarAngle(Vector2D(central_point, vertices_[j])))*/
			{
				l = (i + 1) % num_of_vertices;
			}
		}
		else if (cpoint_p0.PolarAngle(cpoint_point) == cpoint_p0.PolarAngle(Vector2D(central_point, vertices_[i])))
		{
			contains = (central_point.l2_distance(vertices_[i]) >= central_point.l2_distance(point));
			break;
		}
		else /*if (cpoint_p0.PolarAngle(cpoint_point) < cpoint_p0.PolarAngle(Vector2D(central_point, vertices_[i])))*/
		{
			r = i;
		}
	}

	return contains;
}

bool Convex2D::Boundary(const Point2D & p) const
{
	return 0;
}

bool Convex2D::Intersect(const Segment2D& seg, Point2D& p1, Point2D& p2) const
{
	return 0;
}