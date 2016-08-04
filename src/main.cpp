#include "splash.hpp"

using namespace std;

int main()
{
//--------------------------------------------------------------
//--------------------POLYGON AREA TEST-------------------------
//--------------------------------------------------------------
/*
	cin >> n;
	vector<Point2D> points(n);
	for (int i = 0; i < n; ++i)
		cin >> points[i];

	Polygon polygon_1(points);

	cout << "Polygon area is: " << polygon_1.Area() << "\n";
*/
//--------------------------------------------------------------
//--------------------LOCALIZATION TEST-------------------------
//--------------------------------------------------------------
	/*
	Convex convex_1;

	int n;
	cin >> n;
	vector<Point2D> points(n);
	for (int i = 0; i < n; ++i)
		cin >> points[i];
	convex_1 = points;

	double x, y;
	cin >> x >> y;
	Point2D point(x, y);

	cout << (convex_1.Contains(point) ? "YES" : "NO");
	*/
//--------------------------------------------------------------
//-----------------------ANGLE TEST-----------------------------
//--------------------------------------------------------------
	/*
	Vector2D first_vec(1, 0);
	Vector2D second_vec(1, 0);

	cout << first_vec.polar_angle(second_vec) << "\n";
	*/

	return 0;
}