// SplashGeom (c) - open-source C++ library for geometry and linear algebra
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
	along with SplashGeom.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef vertex_hpp
#define vertex_hpp

#include "../point2D.hpp"

class Edge;

class Vertex {
public:
    Vertex() : edges(0) { }
    Vertex(const Point2D& point2D_) : point2D(point2D_), edges(0) { }
    Vertex(Point2D&& point2D_) : point2D(point2D_), edges(0) { }
    
    Point2D point2D;
    std::vector<std::shared_ptr<Edge>> edges;
    size_t index;
};

#endif /* vertex_hpp */
