#include <algorithm>
#include <iostream>

#include "splash.hpp"

using namespace std;

int main()
{
/*
	Convex2D convex1, convex2;
	int n1, n2;

	cin >> n1;
	vector<Point2D> points(n1);
	for (int i = 0; i < n1; ++i)
		cin >> points[i];
	convex1 = points;

	cin >> n2;
	points.clear();
	points.resize(n2);
	for (int i = 0; i < n2; ++i)
		cin >> points[i];
	convex2 = points;

	Convex2D convex3 = convex1.GetIntersectionalConvex(convex2);
	cout << "Intersectional convex:\n";
	for (auto i : convex3.GetVertices())
		cout << i << "\n";
	cout << "\n";
*/
	int n;
	cin >> n;
	vector<Point2D> points(n);
	for (int i = 0; i < n; ++i)
		cin >> points[i];

	VoronoiDiagram2D diagram(points);

	system("PAUSE");

	return 0;
}
