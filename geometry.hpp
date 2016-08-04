// Copyright (c) 2016, Ilya Zakharkin, Elena Kirilenko and Nadezhda Kasimova
// All rights reserved.
#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <cmath>

#include <algorithm>
#include <vector>

#ifndef M_PI
#define M_PI 3.1415926535
#endif

#define EPS 1e-9

struct Point
{
	double x;
	double y;
	Point() 
		: x(0), y(0) {}
	Point(double _x, double _y) 
		: x(_x), y(_y) {}
};

double distance(const Point&, const Point&);

struct Segment
{
	Point a;
	Point b;
	double len;
	Segment() 
		: len(0) {}
	Segment(const Point& _a, const Point& _b) 
		: a(_a), b(_b), len(distance(a, b)) {}

	bool point_in_box(const Point&) const;
};

double scalar_mul(const Segment&, const Segment&);

struct Line
{
	double A;
	double B;
	double C;
	Line() 
		: A(0), B(0), C(0) {}
	Line(const Segment& seg)
	{
		A = seg.b.y - seg.a.y;
		B = seg.a.x - seg.b.x;
		C = -A * seg.a.x - B * seg.a.y;
	}
	Line(const Point& a, const Point& b)
	{
		A = b.y - a.y;
		B = a.x - b.x;
		C = -A * a.x - B * a.y;
	}

	int sign(const Point&) const;
	double distance(const Point& p) const;
};

class Shape2D
{
public:
	virtual double Area() const = 0;
	virtual bool IsIn(const Point &) const = 0;
	virtual bool Boundary(const Point &) const = 0;
	virtual bool Intersect(const Segment &, Point&, Point&) const = 0;
};

class Ellipse : public Shape2D
{
protected:
	double little_haxis;
	double big_haxis;
	Point center;
public:
	Ellipse()
		: little_haxis(0), big_haxis(0), center() {}

	void SetLittleAx(double);
	void SetBigAx(double);
	void SetCenter(const Point&);

	void GetLittleAx(double);
	void GetBigAx(double);
	void GetCenter(const Point&);

	double Area() const;
	bool IsIn(const Point &) const;
	bool Boundary(const Point &) const;
	bool Intersect(const Segment &, Point&, Point&) const;
};

#endif /*GEOMETRY_H_*/