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

#ifndef DelaunayTriangulationBuilder_hpp
#define DelaunayTriangulationBuilder_hpp

#include <stdio.h>
#include "vertex.hpp"
#include "edge.hpp"
#include "graph.hpp"
#include "point2D.hpp"

class DelaunayTriangulationBuilder {
public:
    DelaunayTriangulationBuilder() { }
    void build(const std::vector<Point2D>&);
    
    Graph get_result();
    bool check();
    
private:
    void resort_vertices(const std::vector<std::unique_ptr<Vertex>>::iterator&, const std::vector<std::unique_ptr<Vertex>>::iterator&, bool);
    static double polar_angle(const Point2D&);
    
    std::pair<Edge*, Edge*> add_common_tangents(const std::vector<std::unique_ptr<Vertex>>::iterator& begin,const std::vector<std::unique_ptr<Vertex>>::iterator& middle,const std::vector<std::unique_ptr<Vertex>>::iterator& end);
    
    void build(const std::vector<std::unique_ptr<Vertex>>::iterator& begin,const std::vector<std::unique_ptr<Vertex>>::iterator& end, bool split_by_x);
    
    // invariant for first edge:
    //          (1)
    // outer    / inner
    //  part   /   part
    //       (2)
    void merge_triangulations(Edge* first, Edge* last);
    
    // ab intersects cd
    static bool intersect(Vertex* a, Vertex* b, Vertex* c, Vertex* d) {
        for (int i = 0; i < 2; ++i) {
            auto straight = b->point2D - a->point2D;
            auto to_first = c->point2D - a->point2D;
            auto to_second = d->point2D - a->point2D;
            if (sign(vector_production(straight, to_first)) *
                sign(vector_production(straight, to_second)) > -1e-4) {
                return false;
            }
            std::swap(a, c);
            std::swap(b, d);
        }
        return true;
    }
    
    void build_stupid(const std::vector<std::unique_ptr<Vertex>>::iterator&, const std::vector<std::unique_ptr<Vertex>>::iterator&);
    
    static int sign(double x) {
        if (x > 1e-6) {
            return 1;
        }
        if (x < -1e-6) {
            return -1;
        }
        return 0;
    }
    
    bool try_all_flips(Edge*);
    
    //      B
    //     / \
    //    A__C
    //    \  /
    //     D
    bool try_flip(Vertex*, Vertex*, Vertex*, Vertex*);
    
    static double get_angle_between(const Point2D& first, const Point2D& second) {
        return std::abs(atan2(vector_production(first, second), scalar_production(first, second)));
    }
    
    static double scalar_production(const Point2D& lhs, const Point2D& rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }
    
    static double vector_production(const Point2D& lhs, const Point2D& rhs) {
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }
    
    Graph result;
};

#endif /* DelaunayTriangulationBuilder_hpp */
