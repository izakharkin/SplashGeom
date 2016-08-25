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
#ifndef EVENT_HPP
#define EVENT_HPP

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

#include "point2D.hpp"

class Event
{
public:
	Event(const Point2D& point_of_event);
	virtual Point2D GetPointOfEvent() const;
	bool operator <(const Event& second_event) const;
protected:
	Point2D point_of_event_;
};

class PointEvent : public Event
{
public:
	PointEvent(const Point2D& site);

	double Abscissa() const;
	double Ordinate() const;
};

class CircleEvent : public Event
{
public:
	CircleEvent(const Point2D& new_voronoi_vertex);

	double Abscissa() const;
	double Ordinate() const;
};

#endif /* EVENT_HPP */