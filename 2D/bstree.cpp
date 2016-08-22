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
#include "bstree.hpp"

BeachNode::BeachNode()
: arc_(nullptr), break_point_(nullptr), parent_(nullptr), left_node_(nullptr), right_node_(nullptr) {}

BeachNode::BeachNode(const Arc& arc)
	: arc_(make_shared<Arc>(arc)), break_point_(nullptr), parent_(nullptr), left_node_(nullptr), right_node_(nullptr) {}

BeachNode::BeachNode(const Point2D& break_point)
	: arc_(nullptr), break_point_(make_shared<Point2D>(break_point)), parent_(nullptr), left_node_(nullptr), right_node_(nullptr) {}

Arc::Arc()
	: focus_(nullptr) {}

Arc::Arc(const PointEvent& focus)
	: focus_(make_shared<Point2D>(focus.GetPointOfEvent())) {}

double Arc::Abscissa() const
{
	return this->focus_->x;
}

double Arc::Ordinate() const
{
	return this->focus_->y;
}

Point2D Arc::GetIntersection(const Arc& second_arc, double line_pos) const
{
	Point2D intersect_point;
	double p1 = 2 * (line_pos - this->focus_->y);
	double p2 = 2 * (line_pos - second_arc.focus_->y);
	// solving the equation
	double a1 = 1 / p1;
	double a2 = 1 / p2;
	double a = a2 - a1;
	double b1 = -this->focus_->x / p1;
	double b2 = -second_arc.focus_->x / p2;
	double b = b2 - b1;
	double c1 = pow(this->focus_->x, 2) + pow(this->focus_->y, 2) - pow(line_pos, 2) / p1;
	double c2 = pow(second_arc.focus_->x, 2) + pow(second_arc.focus_->y, 2) - pow(line_pos, 2) / p1;
	double c = c2 - c1;
	double D = pow(b, 2) - 4 * a * c;
	double x1 = (-b - sqrt(D)) / (2 * a);
	double x2 = (-b + sqrt(D)) / (2 * a);
	double y1 = a1 * pow(x1, 2) + b1 * x1 + c1;
	double y2 = a1 * pow(x2, 2) + b1 * x2 + c1;
	// we need the lower point
	intersect_point = (y1 < y2 ? Point2D(x1, y1) : Point2D(x2, y2));
	return intersect_point;
}

BeachSearchTree::BeachSearchTree()
	: root_(nullptr), the_leftest_leaf_(nullptr) {}

void BeachSearchTree::AddArc(const Arc& new_arc)
{
	if (this->root_ == nullptr) {
		this->root_ = make_shared<BeachNode>(BeachNode(new_arc));
	} else {

	}
}

void BeachSearchTree::DeleteArc(const Arc& arc_to_del)
{
	if (root_ == nullptr) {
		return;
	} else {
//		BeachNode node_to_del = this->SearchArc(arc_to_del);
//		this->DeleteNode(node_to_del);
	}
}

void BeachSearchTree::HandlePointEvent(const PointEvent& point_event, DCEL& edges)
{
	Arc new_arc(point_event);
	this->AddArc(new_arc);
}

void BeachSearchTree::HandleCircleEvent(const CircleEvent& circle_event, DCEL& edges)
{

}