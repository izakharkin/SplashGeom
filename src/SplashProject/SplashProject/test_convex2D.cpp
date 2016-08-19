#include <algorithm>
#include <iostream>

#include "splash.hpp"

using namespace std;

int main()
{
	Convex2D conv1, conv2;
	int n1, n2;

	cin >> n1;
	vector<Point2D> points(n1);
	for (int i = 0; i < n1; ++i)
		cin >> points[i];

	cin >> n2;
	points.clear();
	points.resize(n2);
	for (int i = 0; i < n2; ++i)
		cin >> points[i];

	for_each(conv1.GetVertices().begin(), conv1.GetVertices().end(), 
			[](const Point2D& cur_point) { cout << cur_point << ' '; });

	return 0;
}