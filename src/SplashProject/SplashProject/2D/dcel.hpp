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
#ifndef DCEL_HPP_
#define DCEL_HPP_

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

#include "point2D.hpp"
#include "segment2D.hpp"

class EdgeNode
{
public:
	EdgeNode();
	EdgeNode(const Point2D& p1, const Point2D& p2);
private:
	Segment2D edge;
	shared_ptr<Point2D> start_point_;
	shared_ptr<Point2D> end_point_;
	shared_ptr<EdgeNode> next_edge_;
	shared_ptr<EdgeNode> prev_edge_;
	shared_ptr<EdgeNode> twin;
	shared_ptr<Point2D> site;
};

class DCEL
{
public:
	DCEL();
	
	void AddEdge(const Segment2D&);
private:
	list<EdgeNode> edges;
};

#endif /*DCEL_HPP_*/