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
    void build(const std::vector<Point2D>& points);
    
    Graph get_result();
    
    bool check();
private:
    void resort_vertices(const std::vector<std::shared_ptr<Vertex>>::iterator& begin,
                         const std::vector<std::shared_ptr<Vertex>>::iterator& end, bool by_x);
    
    static double polar_angle(const Point2D& point);
    
    std::pair<std::shared_ptr<Edge>, std::shared_ptr<Edge>>
    add_common_tangents(const std::vector<std::shared_ptr<Vertex>>::iterator& begin,
                        const std::vector<std::shared_ptr<Vertex>>::iterator& middle,
                        const std::vector<std::shared_ptr<Vertex>>::iterator& end);
    
    void build(const std::vector<std::shared_ptr<Vertex>>::iterator& begin,
               const std::vector<std::shared_ptr<Vertex>>::iterator& end, bool split_by_x);
    
    // invariant for first edge:
    //          (1)
    // outer    / inner
    //  part   /   part
    //       (2)
    void merge_triangulations(const std::shared_ptr<Edge>& first,
                              const std::shared_ptr<Edge>& last);
    
    // ab intersects cd
    static bool intersect(std::shared_ptr<Vertex> a,
                          std::shared_ptr<Vertex> b,
                          std::shared_ptr<Vertex> c,
                          std::shared_ptr<Vertex> d);
    
    void build_stupid(const std::vector<std::shared_ptr<Vertex>>::iterator& begin,
                      const std::vector<std::shared_ptr<Vertex>>::iterator& end);
    
    bool try_all_flips(const std::shared_ptr<Edge>& edge);
    
    //      B
    //     / \
    //    A__C
    //    \  /
    //     D
    bool try_flip(const std::shared_ptr<Vertex>& a,
                  const std::shared_ptr<Vertex>& b,
                  const std::shared_ptr<Vertex>& c,
                  const std::shared_ptr<Vertex>& d);
    
    // Helper functions
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
