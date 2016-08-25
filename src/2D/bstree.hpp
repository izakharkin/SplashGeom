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
#ifndef BST_HPP_
#define BST_HPP_

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

#include "point2D.hpp"
#include "event.hpp"
#include "dcel.hpp"

class BeachSearchTree;

class Arch
{
public:
	Arch();
	Arch(const PointEvent& focus);

	double Abscissa() const; // of focus
	double Ordinate() const; // of focus

	Point2D GetIntersection(const Line2D& line) const;
	Point2D GetIntersection(const Ray2D& ray) const;
	pair<Point2D, Point2D> GetIntersection(const Arch& second_arch, double line_position) const;

	bool operator ==(const Arch& second_arch) const;
	bool operator !=(const Arch& second_arch) const;
private:
	shared_ptr<Point2D> focus_;
	shared_ptr<EdgeNode> left_edge_;
	shared_ptr<EdgeNode> right_edge_;
};
// LEAFS are ARCHS
class BeachNode
{
public:
	BeachNode();
	BeachNode(const Arch& arch);
	BeachNode(const Point2D& break_point);
private:
	shared_ptr<Arch> arch_;
	Point2D break_point_;
	shared_ptr<BeachNode> parent_;
	shared_ptr<BeachNode> left_node_;
	shared_ptr<BeachNode> right_node_;
	shared_ptr<EdgeNode> edge_;
	shared_ptr<CircleEvent> circle_event_;

	friend class BeachSearchTree;
};

class BeachSearchTree
{
public:
	BeachSearchTree();
	BeachSearchTree(const shared_ptr<BeachNode>& beach_node);

	void AddArch(const Arch& new_arch, const Rectangle& border_box, priority_queue<Event>& events_queue, DCEL& edges);
	shared_ptr<BeachNode> SearchPlaceForArch(const Arch& arch_to_search) const;

	void DeleteArch(const Arch& new_arch, const Rectangle& border_box, priority_queue<Event>& events_queue, DCEL& edges);
	shared_ptr<BeachNode> SearchArch(const Arch& arch_to_search) const;

	void CheckCircleEvent(const shared_ptr<BeachNode>& arch, const Rectangle& border_box, priority_queue<Event>& events_queue, DCEL& edges);

	shared_ptr<BeachNode> GetTheLeftestLeaf() const;
	shared_ptr<BeachNode> GetNextLeaf(const shared_ptr<BeachNode>& cur_leaf) const;
	// we can push the new event or a new edge at any moment, so they can`t be constant arguments 
	void HandlePointEvent(const PointEvent& point_event, const Rectangle& border_box, priority_queue<Event>& events_queue, DCEL& edges);
	void HandleCircleEvent(const CircleEvent& circle_event, const Rectangle& border_box, priority_queue<Event>& events_queue, DCEL& edges);
private:
	shared_ptr<BeachNode> root_;
};

#endif /*BST_HPP_*/