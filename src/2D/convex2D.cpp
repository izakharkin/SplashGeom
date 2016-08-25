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
#include "convex2D.hpp"

Convex2D::Convex2D()
	: Polygon(), cur_vertex_ind(0) {}

Convex2D::Convex2D(int n)
	: Polygon(n), cur_vertex_ind(0) {}

Convex2D::Convex2D(const Convex2D& second_polygon)
	: Polygon(second_polygon), cur_vertex_ind(second_polygon.cur_vertex_ind) {}

Convex2D& Convex2D::operator =(const Convex2D& second_polygon)
{
	vertices_ = second_polygon.vertices_;
	cur_vertex_ind = second_polygon.cur_vertex_ind;
	return *this;
}

Convex2D::Convex2D(const vector<Point2D>& points)
	: Polygon(points), cur_vertex_ind(0) {}

Convex2D& Convex2D::operator =(const vector<Point2D>& points)
{
	vertices_ = points;
	cur_vertex_ind = 0;
	return *this;
}

Convex2D::Convex2D(Convex2D&& second_polygon)
{
	vertices_ = std::move(second_polygon.vertices_);
	cur_vertex_ind = second_polygon.cur_vertex_ind;
}

Convex2D& Convex2D::operator =(Convex2D&& second_polygon)
{
	vertices_ = std::move(second_polygon.vertices_);
	cur_vertex_ind = second_polygon.cur_vertex_ind;
	return *this;
}

void Convex2D::AddVertex(const Point2D& new_vertex)
{
	vertices_.push_back(new_vertex);
	this->MoveCurVertex();
}

size_t Convex2D::Size() const
{
	return vertices_.size();
}

Point2D Convex2D::Next(int i) const
{
	return vertices_[(i + 1) % this->Size()];
}

Point2D Convex2D::Prev(int i) const
{
	return vertices_[(i == 0 ? this->Size() - 1 : i - 1)];
}

Point2D Convex2D::GetLastVertex() const
{
	return vertices_[this->Size()-1];
}

Point2D Convex2D::GetLastPrevVertex() const
{
	return this->Prev(this->Size() - 1);
}

Point2D Convex2D::GetCurVertex() const
{
	return vertices_[cur_vertex_ind];
}
void Convex2D::MoveCurVertex()
{
	cur_vertex_ind = (cur_vertex_ind + 1) % this->Size();
}

Segment2D Convex2D::GetCurEdge() const
{
	return Segment2D(this->GetCurVertex(), Next(cur_vertex_ind));
}

vector<Point2D> Convex2D::GetVertices() const
{
	return vertices_;
}

vector<Segment2D> Convex2D::GetEdges() const
{
	vector<Segment2D> edges;
	for (int i = 0, sz = vertices_.size(); i < sz; ++i) {
		int j = (i + 1) % sz;
		edges.push_back(Segment2D(vertices_[i], vertices_[j]));
	}
	return edges;
}

vector<Point2D> MakeConvexHullGrehem(const vector<Point2D>& points)
{
	vector<Point2D> vertices_ = points;
	Point2D p0 = vertices_[0];
	int position = 0;
	for (size_t i = 1; i < vertices_.size(); ++i) {
		if (p0.y > vertices_[i].y || (p0.y == vertices_[i].y && p0.x < vertices_[i].x)) {
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
			return cos_angle_a > cos_angle_b; // the more angle is the less his cos
	});
	vector <Point2D> convex_hull;
	convex_hull.push_back(vertices_[vertices_.size() - 1]);
	convex_hull.push_back(p0);
	size_t i = 0;
	while (i < vertices_.size())
	{
		if ((vertices_[i].x - convex_hull[convex_hull.size() - 2].x) * (convex_hull[convex_hull.size() - 1].y - convex_hull[convex_hull.size() - 2].y)
			- (vertices_[i].y - convex_hull[convex_hull.size() - 2].y) * (convex_hull[convex_hull.size() - 1].x - convex_hull[convex_hull.size() - 2].x) < 0) {
			convex_hull.push_back(vertices_[i]);
			i++;
		}
		else
			convex_hull.pop_back();
	}
	convex_hull.pop_back();
	return convex_hull;
}

vector<Point2D> MakeConvexHullJarvis(const vector<Point2D>& points)
{
	vector<Point2D> vertices_ = points;
	Point2D p0 = vertices_[0];
	int position_p0 = 0;
	for (size_t i = 1; i < vertices_.size(); ++i) {
		if (p0.y < vertices_[i].y || (p0.y == vertices_[i].y && p0.x < vertices_[i].x)) {
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
	double vect_comp = 0.0;
	while (flag) {
		for (size_t i = 1; i < vertices_.size(); ++i) {
			Vector2D first_vect(convex_hull[cur_index], vertices_[min]);
			Vector2D second_vect(convex_hull[cur_index], vertices_[i]);
			vect_comp = first_vect.OrientedCCW(second_vect);
			if (vect_comp < 0 || (vect_comp == 0 && first_vect.Norm() < second_vect.Norm()))
				min = i;
		}
		cur_index++;
		convex_hull.push_back(vertices_[min]);
		min = 0;
		if (convex_hull[cur_index] == convex_hull[0]) {
			flag = false;
			convex_hull.erase(convex_hull.begin() + cur_index);
		}
	}
	return convex_hull;
}

double Convex2D::Area() const
{
	return Polygon::Area();
}

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
	while (r - l > 0) {
		int i = (l + r) >> 1;
		if (cpoint_p0.PolarAngle(cpoint_point) > cpoint_p0.PolarAngle(Vector2D(central_point, vertices_[i]))) {
			int j = (i + 1) % num_of_vertices;
			if (cpoint_p0.PolarAngle(cpoint_point) < cpoint_p0.PolarAngle(Vector2D(central_point, vertices_[j]))) {
				Vector2D point_pi(point, vertices_[i]);
				Vector2D pi_pj(vertices_[i], vertices_[j]);
				contains = (point_pi.OrientedCCW(pi_pj) >= 0);
				break;
			} else if (cpoint_p0.PolarAngle(cpoint_point) == cpoint_p0.PolarAngle(Vector2D(central_point, vertices_[j]))) {
				contains = (central_point.l2_distance(vertices_[j]) >= central_point.l2_distance(point));
				break;
			} else /* if (cpoint_p0.PolarAngle(cpoint_point) > cpoint_p0.PolarAngle(Vector2D(central_point, vertices_[j]))) */ {
				l = (i + 1) % num_of_vertices;
			}
		} else if (cpoint_p0.PolarAngle(cpoint_point) == cpoint_p0.PolarAngle(Vector2D(central_point, vertices_[i]))) {
			contains = (central_point.l2_distance(vertices_[i]) >= central_point.l2_distance(point));
			break;
		} else /* if (cpoint_p0.PolarAngle(cpoint_point) < cpoint_p0.PolarAngle(Vector2D(central_point, vertices_[i]))) */ {
			r = i;
		}
	}
	return contains;
}

double Convex2D::Perimeter() const
{
	return Polygon::Perimeter();
}

bool Convex2D::Boundary(const Point2D& point) const
{
	return Polygon::Boundary(point);
}

vector<Point2D> Convex2D::GetIntersection(const Line2D& line) const
{
	return Polygon::GetIntersection(line);
}

vector<Point2D> Convex2D::GetIntersection(const Ray2D& ray) const
{
	return Polygon::GetIntersection(ray);
}

vector<Point2D> Convex2D::GetIntersection(const Segment2D& segment) const
{
	return Polygon::GetIntersection(segment);
}

NumOfCase EdgesCaseNum(const Segment2D& first_edge, const Segment2D& second_edge)
{
	bool first_looks_at_second = first_edge.LooksAt(second_edge);
	bool second_looks_at_first = second_edge.LooksAt(first_edge);
	if (first_looks_at_second && second_looks_at_first) {
		return NumOfCase::kBothLooks;
	} else if (first_looks_at_second) {
		return NumOfCase::kFirstLooksAtSecond;
	} else if (second_looks_at_first) {
		return NumOfCase::kSecondLooksAtFirst;
	} else {
		return NumOfCase::kBothNotLooks;
	}
}

WhichEdge WhichEdgeIsInside(const Segment2D& first_edge, const Segment2D& second_edge)
{
	double first_second_side = Vector2D(second_edge).OrientedCCW(Vector2D(second_edge.a, first_edge.b));
	double second_first_side = Vector2D(first_edge).OrientedCCW(Vector2D(first_edge.a, second_edge.b));
	if (first_second_side < 0) {
		return WhichEdge::kSecondEdge;
	} else if (second_first_side < 0) {
		return WhichEdge::kFirstEdge;
	} else {
		return WhichEdge::Unknown;
	}
}

WhichEdge MoveOneOfEdges(const Segment2D& first_edge, const Segment2D& second_edge, Convex2D& result_polygon)
{
	WhichEdge now_inside = WhichEdgeIsInside(first_edge, second_edge);
	NumOfCase case_num = EdgesCaseNum(first_edge, second_edge);
	WhichEdge which_edge_is_moving;
	switch (case_num) {
		case NumOfCase::kBothLooks: {
			if (now_inside == WhichEdge::kFirstEdge) {
				which_edge_is_moving = WhichEdge::kSecondEdge;
			} else {
				which_edge_is_moving = WhichEdge::kFirstEdge;
			}
			break;
		}
		case NumOfCase::kFirstLooksAtSecond: {
			which_edge_is_moving = WhichEdge::kFirstEdge;
			break;
		}
		case NumOfCase::kSecondLooksAtFirst: {
			which_edge_is_moving = WhichEdge::kSecondEdge;
			break;
		}
		case NumOfCase::kBothNotLooks: {
			if (now_inside == WhichEdge::kFirstEdge) {
				which_edge_is_moving = WhichEdge::kSecondEdge;
			} else {
				which_edge_is_moving = WhichEdge::kFirstEdge;
			}
			break;
		}
	}
	if (result_polygon.Size() != 0 && (case_num == NumOfCase::kFirstLooksAtSecond || case_num == NumOfCase::kSecondLooksAtFirst)) {
		Point2D vertex_to_add;
		if (now_inside == WhichEdge::kFirstEdge) {
			vertex_to_add = first_edge.b;
		} else if (now_inside == WhichEdge::kSecondEdge) {
			vertex_to_add = second_edge.b;
		} else { 
			if (case_num == NumOfCase::kFirstLooksAtSecond)
				vertex_to_add = first_edge.b; // !
			else
				vertex_to_add = second_edge.b;
		}
		if (vertex_to_add != result_polygon.GetCurVertex() &&
			vertex_to_add != result_polygon.GetLastPrevVertex())
			result_polygon.AddVertex(vertex_to_add);
	}
	return which_edge_is_moving;
}

Convex2D Convex2D::GetIntersectionalConvex(Convex2D& second_polygon)
{
	Convex2D result_polygon;
	size_t max_iter = 2 * (this->Size() + second_polygon.Size());
	Segment2D cur_fp_edge; // current first polygon edge
	Segment2D cur_sp_edge; // current second polygon edge
	Point2D intersection_point;
	bool no_intersection = true;
	WhichEdge moving_edge = WhichEdge::Unknown;
	for (size_t i = 0; i < max_iter; ++i) {
		cur_fp_edge = this->GetCurEdge();
		cur_sp_edge = second_polygon.GetCurEdge();
		intersection_point = cur_fp_edge.GetIntersection(cur_sp_edge);
		if (intersection_point != kInfPoint2D) {
			if (result_polygon.Size() == 0) {
				no_intersection = false;
				result_polygon.AddVertex(intersection_point);
			} else if (intersection_point != result_polygon.GetCurVertex()) {
				if (intersection_point == result_polygon.vertices_[0]) {
					break; // we already found the intersection polygon
				} else {
					result_polygon.AddVertex(intersection_point);
				}
			}
		}
		moving_edge = MoveOneOfEdges(cur_fp_edge, cur_sp_edge, result_polygon);
		if (moving_edge == WhichEdge::kFirstEdge) {
			this->MoveCurVertex();
		} else {
			second_polygon.MoveCurVertex();
		}
	}
	if (no_intersection == true) {
		if (second_polygon.Contains(this->GetCurVertex())) {
			result_polygon = *this;
		} else if (this->Contains(second_polygon.GetCurVertex())) {
			result_polygon = second_polygon;
		}
	}
	return result_polygon;
}