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

#include "splash_forward.hpp"
#include "splash_utils.hpp"

#include "2D/point2D.hpp"

class BeachNode
{
public:

private:
	shared_ptr<BeachNode> left;
	shared_ptr<BeachNode> right;
};

class Arc : BeachNode
{
public:

private:
	shared_ptr<Point2D> focus;

};

class BeachSearchTree
{
public:
	BeachSearchTree();
	
	void AddArc(const Arc& new_arc);
private:
	shared_ptr<BeachNode> root;
};

#endif /*BST_HPP_*/