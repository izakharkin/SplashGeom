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
#ifndef EVENT_HPP
#define EVENT_HPP

#include "../splash_forward.hpp"
#include "../splash_utils.hpp"

#include "point2D.hpp"

class Event
{
public:
	virtual Point2D GetSomeNew();
	bool operator <(const Event& second_event) const;
protected:
	Point2D point_of_event;
};

class OrdinateOrder
{
public:
	bool operator() (const Point2D& first_point, const Point2D& second_point) {
		return first_point.y > second_point.y || (first_point.y - second_point.y) <= EPS && first_point.x < second_point.x;
	}
};

class PointEvent : public Event
{

};

class CircleEvent : public Event
{

};

#endif /* EVENT_HPP */