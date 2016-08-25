// SplashGeom (c) - open-source C++ library for geometry and linear algebra.
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
	along with SplashGeom. If not, see <http://www.gnu.org/licenses/>.
 */

#include "point3D.hpp"
#include "line3D.hpp"
#include "segment3D.hpp"
#include "plane.hpp"
#include "shape3D.hpp"

class Cube : public Shape3D {
public:
    
    Cube () {}
    Cube (double size_, Point3D origin_): side(size_), origin(origin_) {}
    
    // Resize the cube such that the resulting volume is equal to the factor
    // of the initial volume
    void ScaleCube(double factor);
    
    bool Contains(const Point3D& point) const override;
    bool Boundary(const Point3D& point) const override;
    
    double Volume() const override;
    double SurfaceArea() const override;
    
    Point3D GetOrigin() const;
    double GetSide() const;
    
    // Intersections of line, ray and segment with the cube's boundary
    virtual vector<Point3D> GetIntersection(const Line3D& line) const override;
    virtual vector<Point3D> GetIntersection(const Ray3D& ray) const override;
    virtual vector<Point3D> GetIntersection(const Segment3D& segment) const override;
    
    void SetOrigin(const Point3D& origin_);
    void SetSide(double side_);
    
private:
    Point3D origin;
    double side;
};
