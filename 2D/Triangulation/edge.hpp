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

#ifndef edge_hpp
#define edge_hpp

#include <stdio.h>
#include "point2D.hpp"
#include "vertex.hpp"
#include <array>

class Edge {
public:
    void delete_edge() const;
    
    std::shared_ptr<Vertex> other_vertex(const std::shared_ptr<Vertex>& x) const;
    
    std::array<std::shared_ptr<Vertex>, 2> vertices;
    std::array<size_t, 2> indexes;
};


#endif /* edge_hpp */
