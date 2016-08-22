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

#include "edge.hpp"

void Edge::delete_edge() const {
    for (int i = 0; i < 2; ++i) {
        if (vertices[i]->edges.back()->vertices[0] == vertices[i]) {
            vertices[i]->edges.back()->indexes[0] = indexes[i];
        } else {
            vertices[i]->edges.back()->indexes[1] = indexes[i];
        }
        vertices[i]->edges[indexes[i]] = vertices[i]->edges.back();
        vertices[i]->edges.pop_back();
    }
}

std::shared_ptr<Vertex> Edge::other_vertex(const std::shared_ptr<Vertex>& x) const {
    return vertices[0].get() == x.get() ? vertices[1] : vertices[0];
}
