#include "DelaunayTriangulationBuilder.hpp"
#include <iostream>

void quadrangle_test() {
    DelaunayTriangulationBuilder builder;
    builder.build({Point2D(0, 0), Point2D(0, 1), Point2D(2, 1), Point2D(3, 0)});
    auto result = builder.get_result();
    std::cout << "small test: " << result.vertices.size() << " " << result.edges.size() << std::endl;
}

double get_random_double() {
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX / 100) - 50;
}

void random_test(size_t points_count) {
    std::vector<Point2D> points(points_count);
    for (auto& point : points) {
        point.x = get_random_double();
        point.y = get_random_double();
    }
    DelaunayTriangulationBuilder builder;
    builder.build(points);
    assert(builder.check());
    std::cout << "random test " << points_count << " passed" << std::endl;
}

int main() {
    srand(1337);
    quadrangle_test();
    random_test(5);
    random_test(9);
    for (int i = 0; i < 10; ++i) {
        random_test(6);
    }
    for (int i = 0; i < 100; ++i) {
        random_test(30);
    }
    random_test(228);
    random_test(1000);
    return 0;
}
