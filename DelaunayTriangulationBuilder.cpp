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

#include "DelaunayTriangulationBuilder.hpp"

void DelaunayTriangulationBuilder::build(const std::vector<Point2D>& points) {
    result = std::move(Graph{});
    
    for (const auto& point : points) {
        result.add_vertex(point);
    }
    
    resort_vertices(result.vertices.begin(), result.vertices.end(), true);
    build(result.vertices.begin(), result.vertices.end(), true);
}

Graph DelaunayTriangulationBuilder::get_result() {
    return std::move(result);
}

bool DelaunayTriangulationBuilder::check() {
    for (const auto& vertex : result.vertices) {
        for (const std::shared_ptr<Edge>& edge : vertex->edges) {
            if (try_all_flips(edge)) {
                return false;
            }
        }
    }
    return true;
}

void DelaunayTriangulationBuilder::resort_vertices(const std::vector<std::shared_ptr<Vertex>>::iterator& begin,
                     const std::vector<std::shared_ptr<Vertex>>::iterator& end, bool by_x) {
    if (by_x) {
        std::sort(begin, end,
                  [](const std::shared_ptr<Vertex> &lhs, const std::shared_ptr<Vertex> &rhs) {
                      return lhs->point2D.x < rhs->point2D.x;
                  });
    } else {
        std::sort(begin, end,
                  [](const std::shared_ptr<Vertex> &lhs, const std::shared_ptr<Vertex> &rhs) {
                      return lhs->point2D.y < rhs->point2D.y;
                  });
    }
    
    for (auto it = begin; it < end; ++it) {
        (*it)->index = it - result.vertices.begin();
    }
}

double DelaunayTriangulationBuilder::polar_angle(const Point2D& point) {
    return atan2(point.y, point.x);
}

std::pair<std::shared_ptr<Edge>, std::shared_ptr<Edge>>
DelaunayTriangulationBuilder::add_common_tangents(const std::vector<std::shared_ptr<Vertex>>::iterator& begin,
                    const std::vector<std::shared_ptr<Vertex>>::iterator& middle,
                    const std::vector<std::shared_ptr<Vertex>>::iterator& end) {
    std::shared_ptr<Vertex> right_bottom_vertex = *middle;
    std::shared_ptr<Vertex> right_top_vertex = *middle;
    std::shared_ptr<Vertex> left_bottom_vertex = *(middle - 1);
    std::shared_ptr<Vertex> left_top_vertex = *(middle - 1);
    bool something_changed = true;
    while (something_changed) {
        something_changed = false;
        
        double max_angle = polar_angle(right_top_vertex->point2D - left_top_vertex->point2D);
        double min_angle = polar_angle(right_bottom_vertex->point2D - left_bottom_vertex->point2D);
        for (auto it = middle; it < end; ++it) {
            auto vertex = *it;
            double angle_from_top = polar_angle(vertex->point2D - left_top_vertex->point2D);
            if (angle_from_top > max_angle) {
                max_angle = angle_from_top;
                right_top_vertex = vertex;
                something_changed = true;
            }
            double angle_from_bottom = polar_angle(vertex->point2D - left_bottom_vertex->point2D);
            if (angle_from_bottom < min_angle) {
                min_angle = angle_from_bottom;
                right_bottom_vertex = vertex;
                something_changed = true;
            }
        }
        
        max_angle = polar_angle(right_bottom_vertex->point2D - left_bottom_vertex->point2D);
        min_angle = polar_angle(right_top_vertex->point2D - left_top_vertex->point2D);
        for (auto it = begin; it < middle; ++it) {
            auto vertex = *it;
            double angle_to_top = polar_angle(right_top_vertex->point2D - vertex->point2D);
            if (angle_to_top < min_angle) {
                min_angle = angle_to_top;
                left_top_vertex = vertex;
                something_changed = true;
            }
            double angle_to_bottom = polar_angle(right_bottom_vertex->point2D - vertex->point2D);
            if (angle_to_bottom > max_angle) {
                max_angle = angle_to_bottom;
                left_bottom_vertex = vertex;
                something_changed = true;
            }
        }
    }
    
    return std::make_pair(result.add_edge(result.vertices.begin() + left_bottom_vertex->index,
                                          result.vertices.begin() + right_bottom_vertex->index),
                          result.add_edge(result.vertices.begin() + right_top_vertex->index,
                                          result.vertices.begin() + left_top_vertex->index));
}

void DelaunayTriangulationBuilder::build(const std::vector<std::shared_ptr<Vertex>>::iterator& begin,
           const std::vector<std::shared_ptr<Vertex>>::iterator& end, bool split_by_x) {
    if (end - begin < 6) {
        build_stupid(begin, end);
        return;
    }
    std::shared_ptr<Edge> first;
    std::shared_ptr<Edge> last;
    std::vector<std::shared_ptr<Vertex>>::iterator middle;
    if (split_by_x) {
        middle = begin + (end - begin) / 2;
        while (middle < end && (*middle)->point2D.x == (*(middle - 1))->point2D.x) {
            ++middle;
        }
    } else {
        middle = begin + (end - begin) / 2;
        while (middle < end && (*middle)->point2D.y == (*(middle - 1))->point2D.y) {
            ++middle;
        }
    }
    if (middle == end) {
        resort_vertices(begin, end, !split_by_x);
        build(begin, end, !split_by_x);
        return;
    }
    
    build(begin, middle, split_by_x);
    build(middle, end, split_by_x);
    
    auto tangents = add_common_tangents(begin, middle, end);
    
    merge_triangulations(tangents.first, tangents.second);
    
    std::cout << "result:\n";
    for (auto it = begin; it != end; ++it) {
        std::cout << (*it)->index << "(" << (*it)->point2D.x << " " << (*it)->point2D.y << "): ";
        Graph::print_all_neighbours(*it);
    }
}

void DelaunayTriangulationBuilder::merge_triangulations(const std::shared_ptr<Edge>& first,
                          const std::shared_ptr<Edge>& last) {
    std::shared_ptr<Vertex> similar_vertex;
    for (const std::shared_ptr<Vertex>& v1 : first->vertices) {
        for (const std::shared_ptr<Vertex>& v2 : last->vertices) {
            if (v1.get() == v2.get()) {
                similar_vertex = v1;
                break;
            }
        }
    }
    
    auto current_edge = first->vertices[1]->point2D - first->vertices[0]->point2D;
    auto middle = first->vertices[0]->point2D + (current_edge / 2.0);
    Point2D normal(-current_edge.y, current_edge.x);
    auto edge_length = current_edge.l2_distance(Point2D(0, 0));
    normal = normal / edge_length;
    
    std::array<double, 2> min_dist = {1e9, 1e9};
    std::array<std::shared_ptr<Vertex>, 2> vertices;
    for (int i = 0; i < 2; ++i) {
        for (const std::shared_ptr<Edge>& edge : first->vertices[0]->edges) {
            const Point2D &p = edge->other_vertex(first->vertices[0])->point2D;
            auto ap = p - first->vertices[0]->point2D;
            if (scalar_production(normal, ap) > 0) {
                double side_a = p.l2_distance(first->vertices[0]->point2D);
                double side_b = p.l2_distance(first->vertices[1]->point2D);
                double double_area = std::abs(vector_production(ap, current_edge));
                if (double_area < 1e-6) {
                    continue;
                }
                double r = side_a * side_b * edge_length / (2 * double_area);
                double x = sqrt(r * r - edge_length * edge_length / 4.0);
                assert(std::abs(p.l2_distance(middle + normal * x) - r) < 1e-3 ||
                       std::abs(p.l2_distance(middle - normal * x) - r) < 1e-3);
                if (std::abs(p.l2_distance(middle + normal * x) - r) > 1e-3) {
                    x *= -1;
                }
                if (x < min_dist[i]) {
                    min_dist[i] = x;
                    vertices[i] = edge->other_vertex(first->vertices[0]);
                }
            }
        }
        std::swap(first->vertices[0], first->vertices[1]);
    }
    
    if (std::min(min_dist[0], min_dist[1]) == 1e9) {
        return;
    }
    
    std::shared_ptr<Edge> new_edge;
    int index_to_check;
    if (min_dist[0] < min_dist[1]) {
        new_edge = result.add_edge(result.vertices.begin() + vertices[0]->index,
                                   result.vertices.begin() + first->vertices[1]->index);
        index_to_check = 0;
    } else {
        new_edge = result.add_edge(result.vertices.begin() + first->vertices[0]->index,
                                   result.vertices.begin() + vertices[1]->index);
        index_to_check = 1;
    }
    
    if (new_edge == nullptr) {
        return;
    }
    
    for (size_t i = 0; i < first->vertices[index_to_check]->edges.size(); ++i) {
        std::shared_ptr<Edge> edge = first->vertices[index_to_check]->edges[i];
        if (intersect(edge->vertices[0], edge->vertices[1],
                      new_edge->vertices[0], new_edge->vertices[1])) {
            --i;
            edge->delete_edge();
        }
    }
    
    merge_triangulations(new_edge, last);
}

bool DelaunayTriangulationBuilder::intersect(std::shared_ptr<Vertex> a,
                      std::shared_ptr<Vertex> b,
                      std::shared_ptr<Vertex> c,
                      std::shared_ptr<Vertex> d) {
    for (int i = 0; i < 2; ++i) {
        auto straight = b->point2D - a->point2D;
        auto to_first = c->point2D - a->point2D;
        auto to_second = d->point2D - a->point2D;
        if (sgn(vector_production(straight, to_first)) *
            sgn(vector_production(straight, to_second)) > -1e-4) {
            return false;
        }
        std::swap(a, c);
        std::swap(b, d);
    }
    return true;
}

void DelaunayTriangulationBuilder::build_stupid(const std::vector<std::shared_ptr<Vertex>>::iterator& begin,
                  const std::vector<std::shared_ptr<Vertex>>::iterator& end) {
    std::vector<std::pair<std::vector<std::shared_ptr<Vertex>>::iterator,
    std::vector<std::shared_ptr<Vertex>>::iterator>> edges;
    edges.reserve((end - begin) * (end - begin + 1) / 2);
    for (auto it1 = begin; it1 != end; ++it1) {
        for (auto it2 = it1 + 1; it2 != end; ++it2) {
            edges.emplace_back(it1, it2);
        }
    }
    
    for (size_t i = 0; i < edges.size(); ++i) {
        for (size_t j = i + 1; j < edges.size(); ++j) {
            if (intersect(*edges[i].first, *edges[i].second,
                          *edges[j].first, *edges[j].second)) {
                edges[j] = std::move(edges.back());
                edges.pop_back();
                --j;
            }
        }
    }
    
    for (const auto& edge : edges) {
        result.add_edge(edge.first, edge.second);
    }
    
    bool something_changed = true;
    while (something_changed) {
        something_changed = false;
        for (auto it = begin; it != end; ++it) {
            for (const std::shared_ptr<Edge>& edge : (*it)->edges) {
                if (try_all_flips(edge)) {
                    something_changed = true;
                    break;
                }
            }
        }
    }
}

bool DelaunayTriangulationBuilder::try_all_flips(const std::shared_ptr<Edge>& edge) {  // true if something changed
    auto vertices = result.get_similar_vertices(edge->vertices[0], edge->vertices[1]);
    assert(vertices.size() > 0);
    for (const std::shared_ptr<Vertex>& x : vertices) {
        std::array<std::shared_ptr<Vertex>, 3> triangle{edge->vertices[0], edge->vertices[1], x};
        for (size_t i = 0; i < 2; ++i) {
            for (size_t j = i + 1; j < 3; ++j) {
                auto ys = result.get_similar_vertices(triangle[i], triangle[j]);
                for (const std::shared_ptr<Vertex>& y : ys) {
                    if (try_flip(triangle[i], triangle[3 - i - j], triangle[j], y)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

//      B
//     / \
//    A__C
//    \  /
//     D
bool DelaunayTriangulationBuilder::try_flip(const std::shared_ptr<Vertex>& a,
              const std::shared_ptr<Vertex>& b,
              const std::shared_ptr<Vertex>& c,
              const std::shared_ptr<Vertex>& d) {
    if (!intersect(a, c, b, d)) {
        return false;
    }
    for (std::vector<std::shared_ptr<Edge>>* edges : {&a->edges, &b->edges, &c->edges, &d->edges}) {
        for (const std::shared_ptr<Edge>& edge : *edges) {
            // bd intersects not only ac
            if (!(edge->other_vertex(a) == c && edge->other_vertex(c) == a) &&
                intersect(edge->vertices[0], edge->vertices[1], b, d)) {
                return false;
            }
        }
    }
    auto ab = b->point2D - a->point2D;
    auto ba = -ab;
    auto bc = c->point2D - b->point2D;
    auto cb = -bc;
    auto ac = c->point2D - a->point2D;
    auto ca = -ac;
    auto ad = d->point2D - a->point2D;
    auto da = -ad;
    auto cd = d->point2D - c->point2D;
    auto dc = -cd;
    auto bd = d->point2D - b->point2D;
    auto db = -bd;
    double min_ac_angle = get_angle_between(ab, ac);
    min_ac_angle = std::min(min_ac_angle, get_angle_between(ac, ad));
    min_ac_angle = std::min(min_ac_angle, get_angle_between(ba, bc));
    min_ac_angle = std::min(min_ac_angle, get_angle_between(ca, cb));
    min_ac_angle = std::min(min_ac_angle, get_angle_between(ca, cd));
    min_ac_angle = std::min(min_ac_angle, get_angle_between(da, dc));
    double min_bd_angle = get_angle_between(ba, bd);
    min_bd_angle = std::min(min_bd_angle, get_angle_between(bc, bd));
    min_bd_angle = std::min(min_bd_angle, get_angle_between(ab, ad));
    min_bd_angle = std::min(min_bd_angle, get_angle_between(da, db));
    min_bd_angle = std::min(min_bd_angle, get_angle_between(dc, db));
    min_bd_angle = std::min(min_bd_angle, get_angle_between(cd, cb));
    if (min_ac_angle >= min_bd_angle) {  // OK
        return false;
    }
    for (const std::shared_ptr<Edge>& edge : a->edges) {
        std::shared_ptr<Vertex> not_a = edge->other_vertex(a);
        if (not_a.get() == c.get()) {
            edge->delete_edge();
            result.add_edge(result.vertices.begin() + b->index, result.vertices.begin() + d->index);
            return true;
        }
    }
    // must be unreachable code
    assert(false);
}
