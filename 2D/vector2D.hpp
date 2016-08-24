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
#ifndef VECTOR2D_HPP_
#define VECTOR2D_HPP_

#include "splash_forward.hpp"
#include "splash_utils.hpp"

#include "point2D.hpp"
#include "segment2D.hpp"

class Vector2D
{
public:
	double x1;
	double x2;

	Vector2D();
	Vector2D(double _x1, double _x2);
	Vector2D(const Point2D& point_to);
	Vector2D(const Point2D& point_from, const Point2D& point_to);
	Vector2D(const Segment2D& segment);

	// Get the dot product of this vector and sceond_vec
	// Complexity: O(1)
	double Dot(const Vector2D& second_vector) const;
	// Get the oriented area of parallelogramm, built by this two vectors (2D cross product)
	// Counter-Clockwise is a positive rotation
	// Complexity: O(1)
	double OrientedCCW(const Vector2D& second_vector) const; // cross product

	// Get the signed angle between this vector and the second_vec (in this order)
	// Complexity: O(1)
	double OrientedAngle(const Vector2D& second_vector) const;
	// Get the polar angle between this vector and the second_vec (in this order)
	// Returns angle in [0, 2*pi)
	// Complexity: O(1)
	double PolarAngle(const Vector2D& second_vector) const;
	// Get the unsigned angle between this vector and the second_vec (in this order)
	// Complexity: O(1)
	double AbsAngle(const Vector2D& second_vector) const;
	// Get the norm of this vector (sqrt(vec.Dot(vec))
	// Complexity: O(1)
	double Norm() const;
	// Get the ortoganal vector gor this vector
	// Complexity: O(1)
	Vector2D Ortopair() const;

	friend Point2D operator + (const Point2D& point_for_add, const Vector2D& vec_to_add);
};

#endif /*VECTOR2D_HPP_*/
