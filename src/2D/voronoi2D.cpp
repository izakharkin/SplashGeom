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
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with SplashGeom. If not, see <http://www.gnu.org/licenses/>.
*/
#include "voronoi2D.hpp"

Voronoi2DLocus::Voronoi2DLocus()
	: region_(nullptr), site_() {}

Voronoi2DLocus::Voronoi2DLocus(const Convex2D& locus, const Point2D& site)
	: region_(make_shared<Convex2D>(locus)), site_(site) {}

Convex2D Voronoi2DLocus::GetRegion()
{
	return *region_;
}

VoronoiDiagram2D::VoronoiDiagram2D()
	: diagram_() {}

VoronoiDiagram2D::VoronoiDiagram2D(const vector<Point2D>& points)
{
	MakeVoronoiDiagram2DHalfPlanes(points, kMaxRectangle);
}

vector <Voronoi2DLocus> VoronoiDiagram2D::GetDiagramLocuses() const
{
	return diagram_;
}

DCEL VoronoiDiagram2D::GetDiagramDCEL() const
{
	return dcel_;
}

Convex2D GetHalfPlanesIntersection(const Point2D& cur_point, const vector<Line2D>& halfplanes, const Rectangle& border_box)
{
	if (halfplanes.size() == 1) {
		Convex2D cur_convex(border_box.GetIntersectionalConvex2D(cur_point, halfplanes[0]));
		return cur_convex;
	} else {
		int middle = halfplanes.size() >> 1;
		vector<Line2D> first_half(halfplanes.begin(), halfplanes.begin() + middle);
		vector<Line2D> second_half(halfplanes.begin() + middle, halfplanes.end());
		Convex2D first_convex(GetHalfPlanesIntersection(cur_point, first_half, border_box));
		Convex2D second_convex(GetHalfPlanesIntersection(cur_point, second_half, border_box));
		return first_convex.GetIntersectionalConvex(second_convex);
	}
}

Voronoi2DLocus VoronoiDiagram2D::MakeVoronoi2DLocus(const Point2D& site, const vector<Point2D>& points, const Rectangle& border_box)
{
	Voronoi2DLocus cur_locus;
	vector<Line2D> halfplanes;
	for (auto cur_point : points) {
		if (cur_point != site) {
			Segment2D cur_seg(site, cur_point);
			Line2D cur_halfplane(cur_seg.GetCenter(), cur_seg.NormalVec());
			halfplanes.push_back(cur_halfplane);
		}
	}
	*cur_locus.region_ = GetHalfPlanesIntersection(site, halfplanes, border_box);
	cur_locus.site_ = site;
	return cur_locus;
}

VoronoiDiagram2D VoronoiDiagram2D::MakeVoronoiDiagram2DHalfPlanes(const vector<Point2D>& points, const Rectangle& border_box)
{
	Voronoi2DLocus cur_locus;
	for (auto cur_point : points) {
		cur_locus = MakeVoronoi2DLocus(cur_point, points, border_box);
		this->diagram_.push_back(cur_locus);
	}
	return *this;
}

VoronoiDiagram2D VoronoiDiagram2D::MakeVoronoiDiagram2DFortune(const vector<Point2D>& points, const Rectangle& border_box)
{
	priority_queue<Event> events_queue(points.begin(), points.end());
	shared_ptr<Event> cur_event;
	BeachSearchTree beach_line;
	DCEL edges;
	while (!events_queue.empty()) {
		cur_event = make_shared<Event>(events_queue.top());
		shared_ptr<const PointEvent> is_point_event(dynamic_cast<const PointEvent *>(cur_event.get()));
		if (is_point_event) {
			events_queue.pop();
			beach_line.HandlePointEvent(*is_point_event, border_box, events_queue, edges);
		} else {
			shared_ptr<const CircleEvent> is_circle_event(dynamic_cast<const CircleEvent *>(cur_event.get()));
			events_queue.pop();
			beach_line.HandleCircleEvent(*is_circle_event, border_box, events_queue, edges);
		}
	}
	edges.Finish(border_box);
	this->dcel_ = edges;
	return *this;
}