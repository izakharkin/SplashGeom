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
#ifndef CONVEX2D_HPP_
#define CONVEX2D_HPP_

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

#include "polygon.hpp"

class Convex2D : public Polygon
{
public:
	explicit Convex2D();
	explicit Convex2D(int n);

	Convex2D(const Convex2D& second_polygon);
	Convex2D& operator =(const Convex2D& second_polygon);

	Convex2D(const vector<Point2D>& points);
	Convex2D& operator =(const vector<Point2D>& points);

	Convex2D(Convex2D&& second_polygon);
	Convex2D& operator =(Convex2D&& second_polygon);

	void AddVertex(const Point2D& new_vertex);

	size_t Size() const;

	Point2D Next(int i) const;
	Point2D Prev(int i) const;
	Point2D GetCurVertex() const;
	Point2D GetLastVertex() const;
	Point2D GetLastPrevVertex() const;
	void MoveCurVertex();
	Segment2D GetCurEdge() const;

	vector<Point2D> GetVertices() const;
	vector<Segment2D> GetEdges() const;

<<<<<<< HEAD
=======
	vector<Point2D> MakeConvexHullGrehem(const vector<Point2D>& points);
	vector<Point2D> MakeConvexHullJarvis(const vector<Point2D>& points);

>>>>>>> bc3c69d4b8d6868ab5a7b0b7eba9b70116ceb223
	double Area() const;
	bool Contains(const Point2D&) const;
	bool Boundary(const Point2D&) const;
	
	virtual vector<Point2D> GetIntersection(const Line2D&) const override;
	virtual vector<Point2D> GetIntersection(const Ray2D&) const override;
	virtual vector<Point2D> GetIntersection(const Segment2D& segment) const override;

	Convex2D GetIntersectionalConvex(Convex2D& second_polygon);
private:
	size_t cur_vertex_ind;
};

vector<Point2D> MakeConvexHullGrehem(const vector<Point2D>& points);
vector<Point2D> MakeConvexHullJarvis(const vector<Point2D>& points);

enum class NumOfCase
{
	kBothLooks = 1,
	kFirstLooksAtSecond,
	kSecondLooksAtFirst,
	kBothNotLooks,
};

enum class WhichEdge
{
	kFirstEdge = 1,
	kSecondEdge = 2,
	Unknown,
};
// non-member functions for .GetIntersectionalConvex()
NumOfCase EdgesCaseNum(const Segment2D& first_edge, const Segment2D& second_edge);
WhichEdge WhichEdgeIsInside(const Segment2D& first_edge, const Segment2D& second_edge);
WhichEdge MoveOneOfEdges(const Segment2D& first_edge, const Segment2D& second_edge, Convex2D& result_polygon);

#endif /*CONVEX2D_HPP_*/