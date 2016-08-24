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
#include "vector2D.hpp"

Vector2D::Vector2D()
	: x1(), x2() {}

Vector2D::Vector2D(double _x1, double _x2)
	: x1(_x1), x2(_x2) {}

Vector2D::Vector2D(const Point2D& point_to)
	: x1(point_to.x), x2(point_to.y) {}

Vector2D::Vector2D(const Point2D& point_from, const Point2D& point_to)
	: x1(point_to.x - point_from.x), x2(point_to.y - point_from.y) {}

Vector2D::Vector2D(const Segment2D& segment)
	: Vector2D(segment.a, segment.b) {}

double Vector2D::Dot(const Vector2D& second_vec) const 
{
	return (this->x1 * second_vec.x1 + this->x2 * second_vec.x2);
}

double Vector2D::OrientedCCW(const Vector2D& second_vec) const
{
	return (this->x1 * second_vec.x2 - this->x2 * second_vec.x1);
}

double Vector2D::OrientedAngle(const Vector2D& second_vec) const
{
	double dot_product = this->Dot(second_vec);
	double cross_product = this->OrientedCCW(second_vec);
	double angle;
	if (dot_product == 0) {
		angle = M_PI * 0.5;
		if (cross_product < 0) {
			angle *= -1;
		}
	} else {
		angle = atan2(cross_product, dot_product);
		if (dot_product < 0) {
			if (cross_product >= 0) {
				angle += M_PI;
			} else {
				angle -= M_PI;
			}
		}
	}
	return angle;
}

double Vector2D::PolarAngle(const Vector2D& second_vec) const
{
	double dot_product = this->Dot(second_vec);
	double cross_product = this->OrientedCCW(second_vec);
	double angle;
	if (dot_product == 0) {
		angle = M_PI * 0.5;
		if (cross_product < 0) {
			angle += M_PI;
		}
	} else {
		angle = atan2(cross_product, dot_product);
		if (dot_product > 0) {
			if (cross_product < 0) {
				angle = 2 * M_PI + angle; // angle was negative, thats why '+'
			}
		} else /* if (dot_product < 0) */ {
			if (cross_product < 0) {
				angle = 2 * M_PI + angle;
			}
		}
	}
	return angle;
}

double Vector2D::AbsAngle(const Vector2D& second_vec) const
{
	return fabs(this->OrientedAngle(second_vec));
}

double Vector2D::Norm() const
{
	return sqrt(this->Dot(*this));
}

Vector2D Vector2D::Ortopair() const
{
	return Vector2D(-x2, x1);
}

double Vector2D::Length() const
{
	return sqrt(this->x1 * this->x1 + this->x2 * this->x2);
}

Point2D operator + (const Point2D& point, const Vector2D& vec)
{
	return Point2D(point.x + vec.x1, point.y + vec.x2);
}