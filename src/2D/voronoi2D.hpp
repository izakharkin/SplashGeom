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
#ifndef VORONOI2D_HPP_
#define VORONOI2D_HPP_

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

#include "point2D.hpp"
#include "vector2D.hpp"
#include "line2D.hpp"
#include "segment2D.hpp"
#include "polygon.hpp"
#include "convex2D.hpp"
#include "rectangle.hpp"

#include "bstree.hpp"
#include "event.hpp"
#include "dcel.hpp"

class Voronoi2DLocus
{
public:
	Voronoi2DLocus();
	Voronoi2DLocus(const Convex2D& locus, const Point2D& site);

	Convex2D GetRegion();
private:
	shared_ptr<Convex2D> region_;
	Point2D site_;

	friend class VoronoiDiagram2D;
};

Convex2D GetHalfPlanesIntersection(const Point2D& cur_point, const vector<Line2D>& halfplanes, const Rectangle& border_box);

class VoronoiDiagram2D
{
public:
	VoronoiDiagram2D();
	VoronoiDiagram2D(const vector<Point2D>& points);

	vector<Voronoi2DLocus> GetDiagramLocuses() const;
	DCEL GetDiagramDCEL() const;

	VoronoiDiagram2D MakeVoronoiDiagram2DHalfPlanes(const vector<Point2D>& points, const Rectangle& border_box);
	VoronoiDiagram2D MakeVoronoiDiagram2DFortune(const vector<Point2D>& points, const Rectangle& border_box);
private:
	vector<Voronoi2DLocus> diagram_;
	DCEL dcel_;

	Voronoi2DLocus MakeVoronoi2DLocus(const Point2D& cur_point, const vector<Point2D>& points, const Rectangle& border_box);
};

#endif /*VORONOI2D_HPP_*/