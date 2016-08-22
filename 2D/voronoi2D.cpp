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
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Splash. If not, see <http://www.gnu.org/licenses/>.
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

Convex2D GetHalfPlanesIntersection(const Point2D& cur_point, const vector<Line2D>& halfplanes, const Rectangle& border_box)
{
	if (halfplanes.size() == 1) {
		return border_box.GetIntersectionalConvex2D(cur_point, halfplanes[0]);
	} else {
		int middle = halfplanes.size() >> 1;
		vector<Line2D> first_half(halfplanes.begin(), halfplanes.begin() + middle);
		vector<Line2D> second_half(halfplanes.begin() + middle, halfplanes.end());
		Convex2D first_convex = GetHalfPlanesIntersection(cur_point, first_half, border_box);
		Convex2D second_convex = GetHalfPlanesIntersection(cur_point, second_half, border_box);
		return first_convex.GetIntersectionalConvex(second_convex);
	}
}

Voronoi2DLocus VoronoiDiagram2D::MakeVoronoi2DLocus(const Point2D& cur_point, const vector<Point2D>& points, const Rectangle& border_box)
{
	Voronoi2DLocus cur_locus;
	vector<Line2D> halfplanes;
	for (size_t i = 0; i < points.size(); ++i) {
		if (points[i] != cur_point) {
			Segment2D cur_seg(cur_point, points[i]);
			Line2D cur_halfplane(cur_seg.GetCenter(), cur_seg.NormalVec());
			halfplanes.push_back(cur_halfplane);
		}
	}
	*cur_locus.region_ = GetHalfPlanesIntersection(cur_point, halfplanes, border_box);
	cur_locus.site_ = cur_point;
	return cur_locus;
}

VoronoiDiagram2D VoronoiDiagram2D::MakeVoronoiDiagram2DHalfPlanes(const vector<Point2D>& points, const Rectangle& border_box)
{
	Voronoi2DLocus cur_locus;
	for (size_t i = 0; i < points.size(); ++i) {
		cur_locus = MakeVoronoi2DLocus(points[i], points, border_box);
		diagram_.push_back(cur_locus);
	}
	return *this;
}

DCEL VoronoiDiagram2D::MakeVoronoiDiagram2DFortune(const vector<Point2D>& points, const Rectangle& border_box)
{
	priority_queue<PointEvent> point_events(points.begin(), points.end());
	priority_queue<CircleEvent> circle_events;
	shared_ptr<PointEvent> cur_point_event;
	shared_ptr<CircleEvent> cur_circle_event;
	BeachSearchTree beach_line;
	bool no_circle_events = true;
	DCEL edges;

	while (!point_events.empty()) {
		cur_point_event = make_shared<PointEvent>(point_events.top());
		if (!circle_events.empty()) {
			cur_circle_event = make_shared<CircleEvent>(circle_events.top());
			no_circle_events = false;
		}
		if (no_circle_events || cur_point_event > cur_circle_event) {
			beach_line.HandlePointEvent(*cur_point_event, edges);
			point_events.pop();
		} else {
			beach_line.HandleCircleEvent(*cur_circle_event, edges);
			circle_events.pop();
		}
	}

	return edges;
}

// Notes:
//		shared_ptr<PointEvent> which_event;
// 		const shared_ptr<PointEvent> which_event(dynamic_cast<PointEvent*>(cur_event.get()));
//		result_diagram.diagram = MakeDiagramFromList();