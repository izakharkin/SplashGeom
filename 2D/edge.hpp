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
#ifndef EDGE_HPP
#define EDGE_HPP

#include "point2D.hpp"
#include "vertex.hpp"
#include <stdio.h>
#include <array>

class Edge 
{
public:
    array<Vertex*, 2> vertices;
    array<size_t, 2> indexes;
    
    void delete_edge() const;
    Vertex* other_vertex(Vertex*) const;
};

#endif /* EDGE_HPP */
