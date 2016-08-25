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
#include "bstree.hpp"

BeachNode::BeachNode()
	: arch_(nullptr), break_point_(kInfPoint2D), parent_(nullptr), left_node_(nullptr), right_node_(nullptr), edge_(), circle_event_() {}

BeachNode::BeachNode(const Arch& arch)
	: arch_(make_shared<Arch>(arch)), break_point_(kInfPoint2D), parent_(nullptr), left_node_(nullptr), right_node_(nullptr), edge_(), circle_event_() {}

BeachNode::BeachNode(const Point2D& break_point)
	: arch_(nullptr), break_point_(break_point), parent_(nullptr), left_node_(nullptr), right_node_(nullptr), edge_(), circle_event_() {}

Arch::Arch()
	: focus_(nullptr) {}

Arch::Arch(const PointEvent& focus)
	: focus_(make_shared<Point2D>(focus.GetPointOfEvent())) {}

double Arch::Abscissa() const
{
	return this->focus_->x;
}

double Arch::Ordinate() const
{
	return this->focus_->y;
}

bool Arch::operator ==(const Arch& second_arch) const
{
	return *focus_ == *second_arch.focus_;
}

bool Arch::operator !=(const Arch& second_arch) const
{
	return !(*this == second_arch);
}

Point2D Arch::GetIntersection(const Line2D& line) const
{
	return Point2D();
}

Point2D Arch::GetIntersection(const Ray2D& ray) const
{
	Line2D line(ray);
	return this->GetIntersection(line);
}

pair<Point2D, Point2D> Arch::GetIntersection(const Arch& second_arch, double line_pos) const
{
	pair<Point2D, Point2D> intersect_points;
	double p1 = 2 * (line_pos - this->focus_->y);
	double p2 = 2 * (line_pos - second_arch.focus_->y); // is not 0.0, because line moved down
	if (fabs(p1) <= EPS) {
		intersect_points.first = this->GetIntersection(Ray2D(*this->focus_, Point2D(this->focus_->x, this->focus_->y + 1)));
		intersect_points.second = intersect_points.first;
	} else {
		// solving the equation
		double a1 = 1 / p1;
		double a2 = 1 / p2;
		double a = a2 - a1;
		double b1 = -this->focus_->x / p1;
		double b2 = -second_arch.focus_->x / p2;
		double b = b2 - b1;
		double c1 = pow(this->focus_->x, 2) + pow(this->focus_->y, 2) - pow(line_pos, 2) / p1;
		double c2 = pow(second_arch.focus_->x, 2) + pow(second_arch.focus_->y, 2) - pow(line_pos, 2) / p1;
		double c = c2 - c1;
		double D = pow(b, 2) - 4 * a * c;
		if (D < 0) {
			intersect_points = make_pair(kInfPoint2D, kInfPoint2D);
		} else if (fabs(D) <= EPS) {
			double x = -b / (2 * a);
			double y = a1 * pow(x, 2) + b1 * x + c1;
			intersect_points = make_pair(Point2D(x, y), Point2D(x, y));
		} else {
			double x1 = (-b - sqrt(D)) / (2 * a);
			double x2 = (-b + sqrt(D)) / (2 * a);
			double y1 = a1 * pow(x1, 2) + b1 * x1 + c1;
			double y2 = a1 * pow(x2, 2) + b1 * x2 + c1;
			intersect_points = make_pair(Point2D(x1, y1), Point2D(x2, y2));
		}
	}
	return intersect_points;
}

BeachSearchTree::BeachSearchTree()
	: root_(nullptr) {}

BeachSearchTree::BeachSearchTree(const shared_ptr<BeachNode>& beach_node)
	: root_(beach_node) {}

shared_ptr<BeachNode> BeachSearchTree::GetTheLeftestLeaf() const
{
	shared_ptr<BeachNode> cur_node = root_;
	while (cur_node->left_node_ != nullptr)
		cur_node = cur_node->left_node_;
	return cur_node;
}

shared_ptr<BeachNode> BeachSearchTree::GetNextLeaf(const shared_ptr<BeachNode>& cur_leaf) const
{
	if (this->root_->left_node_ == nullptr) {
		return nullptr;
	} else if (cur_leaf->parent_->left_node_ == cur_leaf) {
		if (cur_leaf->parent_->right_node_->arch_ != nullptr) {
			return cur_leaf->parent_->right_node_;
		} else {
			BeachSearchTree subtree(cur_leaf->parent_->right_node_);
			return subtree.GetTheLeftestLeaf();
		}
	} else {
		if (cur_leaf->parent_->parent_->parent_->left_node_ == cur_leaf->parent_->parent_) {
			BeachSearchTree subtree(cur_leaf->parent_->parent_->parent_->right_node_);
			return subtree.GetTheLeftestLeaf();
		} else {
			return nullptr;
		}
	}
}

shared_ptr<BeachNode> BeachSearchTree::SearchArch(const Arch& arch_to_search) const
{
	shared_ptr<BeachNode> cur_node = this->root_;
	if (*cur_node->arch_ != arch_to_search) {
		if (arch_to_search.Abscissa() < cur_node->arch_->Abscissa()) { // it can be BP
			if (cur_node->left_node_ != nullptr) {
				BeachSearchTree subtree(cur_node->left_node_);
				return subtree.SearchArch(arch_to_search);
			} else if (cur_node->left_node_ != nullptr) {
				BeachSearchTree subtree(cur_node->right_node_);
				return subtree.SearchArch(arch_to_search);
			}
		}	
	} else {
		return cur_node;
	}
	return nullptr;
}

shared_ptr<BeachNode> BeachSearchTree::SearchPlaceForArch(const Arch& arch_to_search) const
{
	shared_ptr<BeachNode> cur_node = this->root_;
	if (*cur_node->arch_ != arch_to_search) {
		if (arch_to_search.Abscissa() < cur_node->arch_->Abscissa()) { // it can be BP
			if (cur_node->left_node_ != nullptr) {
				BeachSearchTree subtree(cur_node->left_node_);
				return subtree.SearchArch(arch_to_search);
			}
			else if (cur_node->left_node_ != nullptr) {
				BeachSearchTree subtree(cur_node->right_node_);
				return subtree.SearchArch(arch_to_search);
			}
		}
	}
	else {
		return cur_node;
	}
	return nullptr;
}

void BeachSearchTree::AddArch(const Arch& new_arch, const Rectangle& border_box,
							 priority_queue<Event>& events_queue, DCEL& edges)
{
	if (this->root_ == nullptr) /* no archs yet */ {
		this->root_ = make_shared<BeachNode>(BeachNode(new_arch));
	} else {
		shared_ptr<BeachNode> node_to_split = this->SearchPlaceForArch(new_arch); // this is node with arch, which is intersected by the new arch
		if (node_to_split->break_point_ != kInfPoint2D) /* if the new arch (ray) intersects exactly in break_point */ {

		} else /* ok, the new arch (ray) intersects not in break_point, just split old arch */ {
			pair<Point2D, Point2D> break_points = new_arch.GetIntersection(*node_to_split->arch_, new_arch.Ordinate());
			node_to_split->left_node_ = make_shared<BeachNode>(BeachNode(*node_to_split->arch_));
			node_to_split->left_node_->parent_ = node_to_split;
			node_to_split->break_point_ = break_points.second;
			node_to_split->right_node_ = make_shared<BeachNode>(BeachNode(break_points.second));
			node_to_split->right_node_->parent_ = node_to_split;

			node_to_split->right_node_->left_node_ = make_shared<BeachNode>(BeachNode(new_arch));
			node_to_split->right_node_->left_node_->parent_ = node_to_split->right_node_;
			node_to_split->right_node_->right_node_ = make_shared<BeachNode>(*node_to_split->arch_);
			node_to_split->right_node_->right_node_->parent_ = node_to_split->right_node_;
		}
	}
}

void BeachSearchTree::DeleteArch(const Arch& arch_to_del, const Rectangle& border_box, 
								priority_queue<Event>& events_queue, DCEL& edges)
{
	if (this->root_ == nullptr) {
		return;
	} else {
		shared_ptr<BeachNode> node_to_del = this->SearchArch(arch_to_del);
		
	}
}

void BeachSearchTree::HandlePointEvent(const PointEvent& point_event, const Rectangle& border_box, 
									   priority_queue<Event>& events_queue, DCEL& edges)
{
	Arch new_arch(point_event);
	this->AddArch(new_arch, border_box, events_queue, edges);
}

void BeachSearchTree::HandleCircleEvent(const CircleEvent& circle_event, const Rectangle& border_box, 
										priority_queue<Event>& events_queue, DCEL& edges)
{
	this->DeleteArch(*this->GetTheLeftestLeaf()->arch_, border_box, events_queue, edges);
}
