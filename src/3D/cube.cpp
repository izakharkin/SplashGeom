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
#include "cube.hpp"

vector<Point3D> Cube::GetIntersection(const Ray3D& ray) const {
    vector<Point3D> line = this->GetIntersection(Line3D(ray));
    vector<Point3D> result;
    for (auto it = line.begin(); it != line.end(); it++) {
        if (ray.Contains(*it))
            result.push_back(*it);
    }
    return result;
}

vector<Point3D> Cube::GetIntersection(const Segment3D& segment) const {
    vector<Point3D> line = this->GetIntersection(Line3D(segment));
    vector<Point3D> result;
    for (auto it = line.begin(); it != line.end(); it++) {
        if (segment.Contains(*it))
            result.push_back(*it);
    }
    return result;
}

vector<Point3D> Cube::GetIntersection(const Line3D& line) const {
    
    Point3D p1 = origin;
    Point3D p2 = origin + Point3D(0, 0, side);
    Point3D p3 = origin + Point3D(0, side, 0);
    Point3D p4 = origin + Point3D(side, 0, 0);
    Point3D p5 = origin + Point3D(side, side, 0);
    Point3D p6 = origin + Point3D(side, 0, side);
    Point3D p7 = origin + Point3D(0, side, side);
    
    Plane plane1 = Plane(p1, p2, p3);
    Plane plane2 = Plane(p1, p3, p4);
    Plane plane3 = Plane(p1, p2, p4);
    Plane plane4 = Plane(p3, p5, p7);
    Plane plane5 = Plane(p2, p6, p7);
    Plane plane6 = Plane(p4, p5, p6);
    
    Point3D inter1 = plane1.GetIntersection(line);
    Point3D inter2 = plane2.GetIntersection(line);
    Point3D inter3 = plane3.GetIntersection(line);
    Point3D inter4 = plane4.GetIntersection(line);
    Point3D inter5 = plane5.GetIntersection(line);
    Point3D inter6 = plane6.GetIntersection(line);
    
    vector<Point3D> result;
    if (this->Boundary(inter1))
        result.push_back(inter1);
    if (this->Boundary(inter2))
        result.push_back(inter2);
    if (this->Boundary(inter3))
        result.push_back(inter3);
    if (this->Boundary(inter4))
        result.push_back(inter4);
    if (this->Boundary(inter5))
        result.push_back(inter5);
    if (this->Boundary(inter6))
        result.push_back(inter6);
    return result;
}

void Cube::ScaleCube(double factor) {
    assert(factor >= 0);
    this->SetSide(side * cbrt(factor));
}

bool Cube::Contains(const Point3D &point) const {
    return  point.x >= origin.x &&
            point.y >= origin.y &&
            point.z >= origin.z &&
            point.x <= origin.x + side &&
            point.y <= origin.y + side &&
            point.z <= origin.z + side;
}

bool Cube::Boundary(const Point3D &point) const {
    return this->Contains(point) &&
            (point.x == origin.x ||
             point.x == origin.x + side ||
             point.y == origin.y ||
             point.y == origin.y + side ||
             point.z == origin.z ||
             point.z == origin.z + side);
}

double Cube::Volume() const {
    return side * side * side;
}

double Cube::SurfaceArea() const {
    return 6 * side * side;
}

Point3D Cube::GetOrigin() const {
    return origin;
}

double Cube::GetSide() const {
    return side;
}

void Cube::SetOrigin(const Point3D &origin_) {
    origin = origin_;
}

void Cube::SetSide(double side_) {
    side = side_;
}
