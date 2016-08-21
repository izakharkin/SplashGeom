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

BeachNode::BeachNode(const Arc& arc)
	: arc_(arc) {}

Arc::Arc()
: focus_(nullptr), directrix_pos_(0.0) {}
/*
Arc::Arc(const PointEvent& focus)
	: focus_(make_shared<PointEvent>(focus))
{
	directrix_pos_ = focus_.Ordinate();
}
*/
BeachSearchTree::BeachSearchTree()
	: root_(nullptr) {}

void BeachSearchTree::AddArc(const Arc& new_arc)
{
	if (!root_) {
		root_ = make_shared<BeachNode>(BeachNode(new_arc));
	} else if (0) {

	}
}

void BeachSearchTree::DeleteArc(const Arc& arc_to_del)
{
	if (!root_) {
		return;
	} else if (0) {

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