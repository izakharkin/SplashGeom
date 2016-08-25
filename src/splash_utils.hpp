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
#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <cassert>
#include <cfloat>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <queue>
#include <array>
#include <list>

using std::priority_queue;
using std::make_shared;
using std::shared_ptr;
using std::unique_ptr;
using std::make_pair;
using std::vector;
using std::string;
using std::array;
using std::swap;
using std::move;
using std::list;
using std::pair;

#ifndef M_PI
#define M_PI 3.1415926535
#endif

#ifndef M_E
#define M_E 2.71828182845
#endif

const double EPS = 1e-9;
const double INF = DBL_MAX;

/*constexpr*/int sgn(double d);
vector<double> GetQuadraticSolution(double A, double B, double C);

#endif /*UTILS_HPP_*/