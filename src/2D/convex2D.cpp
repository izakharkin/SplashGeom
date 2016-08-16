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
#include "convex2D.hpp"

Convex2D::Convex2D()
	: Polygon() {}

Convex2D::Convex2D(int n)
	: Polygon(n) {}

Convex2D::Convex2D(const vector<Point2D>& points)
	: Polygon(points) {}

Convex2D::Convex2D(Convex2D&& second_polygon)
{
	vertices_ = std::move(second_polygon.vertices_);
}

void Convex2D::operator =(Convex2D&& second_polygon)
{
	vertices_ = std::move(second_polygon.vertices_);
}

int Convex2D::Size() const
{
	return vertices_.size();
}

Point2D Convex2D::next(int i) const
{
	return vertices_[(i + 1) % this->Size()];
}

Point2D Convex2D::prev(int i) const
{
	return vertices_[(i == 0 ? this->Size() - 1 : i - 1)];
}

Convex2D Convex2D::MakeConvexHullGrehem(const vector<Point2D>& points)
{
	this->vertices_ = points;
	Point2D p0 = vertices_[0];
	int position = 0;

	for (int i = 1; i < vertices_.size(); ++i)
	{
		if (p0.y > vertices_[i].y || (p0.y == vertices_[i].y && p0.x < vertices_[i].x)) 
		{
			p0 = vertices_[i];
			position = i;
		}
	}

	Point2D center;
	vertices_.erase(vertices_.begin() + position);
	sort(vertices_.begin(), vertices_.end(), [&p0](Point2D a, Point2D b)
	{
		double distance_p0_a = p0.l2_distance(a);
		double distance_p0_b = p0.l2_distance(b);
		double cos_angle_a = (a.x - p0.x) / sqrt(distance_p0_a);
		double cos_angle_b = (b.x - p0.x) / sqrt(distance_p0_b);
		if (cos_angle_a == cos_angle_b)
			return distance_p0_a < distance_p0_b;
		else
			return cos_angle_a > cos_angle_b; //the more angle is the less his cos
	});

	vector <Point2D> convex_hull;
	convex_hull.push_back(vertices_[vertices_.size() - 1]);
	convex_hull.push_back(p0);

	int i = 0;
	while (i < vertices_.size())
	{
		if ((vertices_[i].x - convex_hull[convex_hull.size() - 2].x) * (convex_hull[convex_hull.size() - 1].y - convex_hull[convex_hull.size() - 2].y) 
			- (vertices_[i].y - convex_hull[convex_hull.size() - 2].y) * (convex_hull[convex_hull.size() - 1].x - convex_hull[convex_hull.size() - 2].x) < 0)
		{
			convex_hull.push_back(vertices_[i]);
			i++;
		}
		else
			convex_hull.pop_back();
	}
	convex_hull.pop_back();

	return std::move(*this);
}

Convex2D Convex2D::MakeConvexHullJarvis(const vector<Point2D>& points)
{
	this->vertices_ = points;
	Point2D p0 = vertices_[0];
	int position_p0 = 0;

	for (int i = 1; i < vertices_.size(); ++i)
	{
		if (p0.y < vertices_[i].y || (p0.y == vertices_[i].y && p0.x < vertices_[i].x))
		{
			p0 = vertices_[i];
			position_p0 = i;
		}

	}
	vector <Point2D> convex_hull;
	convex_hull.push_back(p0);
	vertices_[position_p0] = vertices_[0];
	vertices_[0] = convex_hull[0];
	int cur_index = 0;
	int min = 1;
	bool flag = true;
	int vect = 0;
	while (flag)
	{
		for (int i = 1; i < vertices_.size(); ++i)
		{
			vect = (vertices_[min].x - convex_hull[cur_index].x) * (vertices_[i].y - convex_hull[cur_index].y) - (vertices_[i].x - convex_hull[cur_index].x) * (vertices_[min].y - convex_hull[cur_index].y);
			if (vect < 0 || (vect == 0 &&
				((convex_hull[cur_index].x - vertices_[min].x) * (convex_hull[cur_index].x - vertices_[min].x) + (convex_hull[cur_index].y - vertices_[min].y) * (convex_hull[cur_index].y - vertices_[min].y) <
				(convex_hull[cur_index].x - vertices_[i].x) * (convex_hull[cur_index].x - vertices_[i].x) + (convex_hull[cur_index].y - vertices_[i].y) * (convex_hull[cur_index].y - vertices_[i].y))))
				min = i;
		}
		cur_index++;
		convex_hull.push_back(vertices_[min]);
		min = 0;
		if (convex_hull[cur_index] == convex_hull[0])
		{
			flag = false;
			convex_hull.erase(convex_hull.begin() + cur_index);
		}
	}

	return std::move(*this);
}

double Convex2D::Area() const
{
	return Polygon::Area();
}

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

Convex2D Convex2D::GetIntersectionalConvex(const Polygon& second_polygon) const
{
	Convex2D result_poly;

	int i, j, k;
	i = j = k = 0;



	return result_poly;
}