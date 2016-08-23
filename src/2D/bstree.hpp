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

class BeachSearchTree;

class Arc
{
public:
	Arc();
	Arc(const PointEvent& focus);

	double Abscissa() const; // of focus
	double Ordinate() const; // of focus

	Point2D GetIntersection(const Line2D& line) const;
	Point2D GetIntersection(const Ray2D& ray) const;
	Point2D GetIntersection(const Arc& second_arc, double line_position) const;

	bool operator ==(const Arc& second_arc) const;
	bool operator !=(const Arc& second_arc) const;
private:
	shared_ptr<Point2D> focus_;
	shared_ptr<EdgeNode> left_edge_;
	shared_ptr<EdgeNode> right_edge_;
};

class BeachNode
{
public:
	BeachNode();
	BeachNode(const Arc& arc);
	BeachNode(const Point2D& break_point);
private:
	shared_ptr<Arc> arc_;
	Point2D break_point_;
	shared_ptr<BeachNode> parent_;
	shared_ptr<BeachNode> left_node_;
	shared_ptr<BeachNode> right_node_;

friend class BeachSearchTree;
};

class BeachSearchTree
{
public:
	BeachSearchTree();

	void AddArc(const Arc& new_arc, const Rectangle& border_box, priority_queue<Event>& events_queue, DCEL& edges);
	shared_ptr<BeachNode> SearchPlaceForArc(const Arc& arc_to_search) const;

	void DeleteArc(const Arc& new_arc, const Rectangle& border_box, priority_queue<Event>& events_queue, DCEL& edges);
	shared_ptr<BeachNode> SearchArc(const Arc& arc_to_search) const;

	void CheckCircleEvent(const shared_ptr<BeachNode>& arc, const Rectangle& border_box, priority_queue<Event>& events_queue, DCEL& edges);

	shared_ptr<BeachNode> GetTheLeftestLeaf() const;
	// we can push the new event or a new edge at any moment, so they can`t be constant arguments 
	void HandlePointEvent(const PointEvent& point_event, const Rectangle& border_box, priority_queue<Event>& events_queue, DCEL& edges);
	void HandleCircleEvent(const CircleEvent& circle_event, const Rectangle& border_box, priority_queue<Event>& events_queue, DCEL& edges);
private:
	shared_ptr<BeachNode> root_;
};

#endif /*BST_HPP_*/