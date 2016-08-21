// Splash (c) - open-source C++ library for geometry and linear algebra
// Copyright (c) 2016, Ilya Zakharkin, Elena Kirilenko and Nadezhda Kasimova.
// All rights reserved.
/*
	This file is part of Splash.
	Splash is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	Foobar is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef graph_hpp
#define graph_hpp

#include <stdio.h>
#include "edge.hpp"
#include "vertex.hpp"

class DelaunayTriangulationBuilder;

class Graph {
public:
    
    std::vector<std::unique_ptr<Vertex>>::iterator add_vertex(const Point2D&);
    std::vector<std::unique_ptr<Vertex>>::iterator add_vertex(Point2D&&);
    
    // Adds an edge between vertex1 and vertex2. Returns nullptr
    // if such an edge exists
    Edge* add_edge(std::vector<std::unique_ptr<Vertex>>::iterator vertex1,std::vector<std::unique_ptr<Vertex>>::iterator vertex2);
    
    // Vertices of the graph
    std::vector<std::unique_ptr<Vertex>> vertices;
    // Vector of edges
    std::vector<std::unique_ptr<Edge>> edges;
    
private:
    
    friend class DelaunayTriangulationBuilder;
    
    static void print_all_neighbours(Vertex*);
    std::vector<Vertex*> get_similar_vertices(Vertex*, Vertex*);
};

#endif /* graph_hpp */
