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
#include "splash_utils.hpp"

/*constexpr*/int sgn(double d)
{
	return (fabs(d) <= EPS ? 0 : (d > 0 ? 1 : -1));
}

vector<double> GetQuadraticSolution(double a, double b, double c)
{
	vector<double> roots;
	double D = pow(b, 2) - 4 * a * c;
	if (fabs(D) <= EPS) {
		double x = -b / (2 * a);
		roots.push_back(x);
	} else if (D > 0) {
		double x1 = (-b - sqrt(D)) / (2 * a);
		double x2 = (-b + sqrt(D)) / (2 * a);
		roots.push_back(x1);
		roots.push_back(x2);
	}
	return roots;
}
