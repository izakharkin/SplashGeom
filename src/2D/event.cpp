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
#include "event.hpp"

Event::Event(const Point2D& point_of_event)
: point_of_event_(point_of_event) {}

Point2D Event::GetPointOfEvent() const
{
	return point_of_event_;
}

bool Event::operator <(const Event& second_event) const
{
	return this->point_of_event_.y > second_event.point_of_event_.y
	   || (this->point_of_event_.y - second_event.point_of_event_.y) <= EPS && this->point_of_event_.x < second_event.point_of_event_.x;
}

PointEvent::PointEvent(const Point2D& site)
	: Event(site) {}

double PointEvent::Abscissa() const
{
	return point_of_event_.x;
}

double PointEvent::Ordinate() const
{
	return point_of_event_.y;
}

CircleEvent::CircleEvent(const Point2D& new_voro_vertex)
	: Event(new_voro_vertex) {}

double CircleEvent::Abscissa() const
{
	return point_of_event_.x;
}

double CircleEvent::Ordinate() const
{
	return point_of_event_.y;
}