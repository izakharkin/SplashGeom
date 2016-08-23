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
	: arc_(nullptr), break_point_(kInfPoint2D), parent_(nullptr), left_node_(nullptr), right_node_(nullptr) {}

BeachNode::BeachNode(const Arc& arc)
	: arc_(make_shared<Arc>(arc)), break_point_(kInfPoint2D), parent_(nullptr), left_node_(nullptr), right_node_(nullptr) {}

BeachNode::BeachNode(const Point2D& break_point)
	: arc_(nullptr), break_point_(break_point), parent_(nullptr), left_node_(nullptr), right_node_(nullptr) {}

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

bool Arc::operator ==(const Arc& second_arc) const
{
	return *focus_ == *second_arc.focus_;
}

bool Arc::operator !=(const Arc& second_arc) const
{
	return !(*this == second_arc);
}

Point2D Arc::GetIntersection(const Line2D& line) const
{
	return Point2D();
}

Point2D Arc::GetIntersection(const Ray2D& ray) const
{
	Line2D line(ray);
	return this->GetIntersection(line);
}

Point2D Arc::GetIntersection(const Arc& second_arc, double line_pos) const
{
	Point2D intersect_point;
	double p1 = 2 * (line_pos - this->focus_->y);
	double p2 = 2 * (line_pos - second_arc.focus_->y); // is not 0.0, because line moved down
	if (fabs(p1) <= EPS) {
		intersect_point = this->GetIntersection(Ray2D(*this->focus_, Point2D(this->focus_->x, this->focus_->y + 1)));
	} else {
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
		if (D < 0) {
			intersect_point = kInfPoint2D;
		} else if (fabs(D) <= EPS) {
			double x = -b / (2 * a);
			double y = a1 * pow(x, 2) + b1 * x + c1;
			intersect_point = Point2D(x, y);
		} else {
			double x1 = (-b - sqrt(D)) / (2 * a);
			double x2 = (-b + sqrt(D)) / (2 * a);
			double y1 = a1 * pow(x1, 2) + b1 * x1 + c1;
			double y2 = a1 * pow(x2, 2) + b1 * x2 + c1;
			intersect_point = (y1 < y2 ? Point2D(x1, y1) : Point2D(x2, y2));
		}
	}
	return intersect_point;
}

BeachSearchTree::BeachSearchTree()
	: root_(nullptr) {}

shared_ptr<BeachNode> BeachSearchTree::GetTheLeftestLeaf() const
{
	shared_ptr<BeachNode> cur_node = root_;
	while (cur_node->left_node_ != nullptr)
		cur_node = cur_node->left_node_;
	return cur_node;
}

shared_ptr<BeachNode> BeachSearchTree::SearchArc(const Arc& arc_to_search) const
{
	shared_ptr<BeachNode> cur_node = this->root_;
	//if (*cur_node->arc_ != arc_to_search) {

	//}
	return nullptr;
}

shared_ptr<BeachNode> BeachSearchTree::SearchPlaceForArc(const Arc& arc_to_search) const
{
	return nullptr;
}

void BeachSearchTree::CheckCircleEvent(const shared_ptr<BeachNode>& arc, const Rectangle& border_box, priority_queue<Event>& events_queue, DCEL& edges)
{
	return;
}

void BeachSearchTree::AddArc(const Arc& new_arc, const Rectangle& border_box,
							 priority_queue<Event>& events_queue, DCEL& edges)
{
	if (this->root_ == nullptr) {
		this->root_ = make_shared<BeachNode>(BeachNode(new_arc));
	} else {
		shared_ptr<BeachNode> break_point = this->SearchPlaceForArc(new_arc); // this is node with arc, which will be implaced with a break point
		if (break_point->arc_->Abscissa() < new_arc.Abscissa()) {
			break_point->left_node_ = make_shared<BeachNode>(*break_point->arc_);
			break_point->right_node_ = make_shared<BeachNode>(new_arc);
		} else {
			break_point->right_node_ = make_shared<BeachNode>(*break_point->arc_);
			break_point->left_node_ = make_shared<BeachNode>(new_arc);
		}
		break_point->left_node_->parent_ = break_point;
		break_point->right_node_->parent_ = break_point;
		break_point->break_point_ = new_arc.GetIntersection(*break_point->arc_, new_arc.Ordinate());
		break_point->arc_ = nullptr; // now it is a break point, not an arc
		// now we must to check if there any new circle events -
		// then push them into the events_queue
		this->CheckCircleEvent(break_point->left_node_, border_box, events_queue, edges);
		this->CheckCircleEvent(break_point->right_node_, border_box, events_queue, edges);
		/*if (break_point->left_node_->arc_ == new_arc) {

		} else {

		}*/
	}
}

void BeachSearchTree::DeleteArc(const Arc& arc_to_del, const Rectangle& border_box, priority_queue<Event>& events_queue, DCEL& edges)
{
	if (this->root_ == nullptr) {
		return;
	} else {
		shared_ptr<BeachNode> node_to_del = this->SearchArc(arc_to_del);
		
	}
}

void BeachSearchTree::HandlePointEvent(const PointEvent& point_event, const Rectangle& border_box, 
									   priority_queue<Event>& events_queue, DCEL& edges)
{
	Arc new_arc(point_event);
	this->AddArc(new_arc, border_box, events_queue, edges);
}

void BeachSearchTree::HandleCircleEvent(const CircleEvent& circle_event, const Rectangle& border_box, 
										priority_queue<Event>& events_queue, DCEL& edges)
{

}