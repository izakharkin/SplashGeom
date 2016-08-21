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
#include "dcel.hpp"

EdgeNode::EdgeNode()
	: edge_(), twin_(nullptr), site_(nullptr) {}

EdgeNode::EdgeNode(const Point2D& p1, const Point2D& p2)
: edge_(p1, p2), twin_(make_shared<EdgeNode>(p2, p1)), site_(nullptr) {}

void DCEL::AddEdge(const EdgeNode& new_edge)
{
	edges.push_back(new_edge);
}