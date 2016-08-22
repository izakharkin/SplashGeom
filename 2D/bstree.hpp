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
#ifndef BST_HPP_
#define BST_HPP_

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

#include "point2D.hpp"
#include "event.hpp"
#include "dcel.hpp"

class Arc
{
public:
	Arc();
	Arc(const PointEvent& focus);

	double Abscissa() const; // of focus
	double Ordinate() const; // of focus

	Point2D GetIntersection(const Arc& second_arc, double line_position) const;
private:
	shared_ptr<Point2D> focus_;
};

class BeachNode
{
public:
	BeachNode();
	BeachNode(const Arc& arc);
	BeachNode(const Point2D& break_point);
private:
	shared_ptr<Arc> arc_;
	shared_ptr<Point2D> break_point_;
	shared_ptr<BeachNode> parent_;
	shared_ptr<BeachNode> left_node_;
	shared_ptr<BeachNode> right_node_;
};

class BeachSearchTree
{
public:
	BeachSearchTree();

	void AddArc(const Arc& new_arc);
	void DeleteArc(const Arc& arc_to_del);
//	BeachNode SearchArc(const Arc& arc_to_search) const;

//	void DeleteNode(const BeachNode& node_to_del);

	void HandlePointEvent(const PointEvent& point_event, DCEL& edges);
	void HandleCircleEvent(const CircleEvent& circle_event, DCEL& edges);
private:
	shared_ptr<BeachNode> root_;
	shared_ptr<BeachNode> the_leftest_leaf_;
};

#endif /*BST_HPP_*/