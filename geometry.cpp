#include "geometry.hpp"
/*
std::ostream& operator << (std::ostream& o, const Point& p)
{
	o << p.x << ' ' << p.y;
	return o;
}
*/
bool operator < (const Point& a, const Point& b)
{
	return a.x < b.x - EPS || fabs(a.x - b.x) < EPS && a.y < b.y - EPS;
}

double distance(const Point& a, const Point& b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double scalar_mul(const Segment& seg1, const Segment& seg2)
{
	return (fabs(seg1.b.x - seg1.a.x) * fabs(seg2.b.x - seg2.a.x) + fabs(seg1.b.y - seg1.a.y) * fabs(seg2.b.y - seg2.a.y));
}

bool Segment::point_in_box(const Point& p) const

{
	return std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x) &&
		std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y);
}

int Line::sign(const Point& p) const
{
	double t = A * p.x + B * p.y + C;
	return (t > 0 ? 1 : (t < 0 ? -1 : 0));
}

double Line::distance(const Point& p) const
{
	return (A * p.x + B * p.y + C / sqrt(A*A + B*B));
}

double Ellipse::Area() const
{
	return M_PI * little_haxis * big_haxis;
}

bool Ellipse::IsIn(const Point &) const
{
	return 0;
}

bool Ellipse::Boundary(const Point &) const
{
	return 0;
}

bool Ellipse::Intersect(const Segment &, Point&, Point&) const
{
	return 0;
}
