// A C++ program to find convex hull of a set of points. Refer
// http://www.geeksforgeeks.org/orientation-3-ordered-points/
// for explanation of orientation()
#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <stack>
#include <stdlib.h>
#include <boost/optional.hpp>


/*
// A globle point needed for  sorting points with reference
// to  the first point Used in compare function of qsort()
Point p0;

// A utility function to find next to top in a stack
Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

// A utility function to swap two points
void swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

// A utility function to return square of distance
// between p1 and p2
int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;

   // Find orientation
   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;

   return (o == 2)? -1: 1;
}

// Prints convex hull of a set of n points.
std::vector<Point> convexHull(std::vector<Point> points)
{
   // Find the bottommost point
   int ymin = points[0].y;
   int min = 0;
   for (int i = 1; i < points.size(); i++) {
	   int y = points[i].y;
		// Pick the bottom-most or chose the left
		// most point in case of tie
		if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
			ymin = points[i].y;
			min = i;
		}
   }

   // Place the bottom-most point at first position
   auto initial = points[0];
   points[0] = points[min];
   points[min] = initial;

   // Sort n-1 points with respect to the first point.
   // A point p1 comes before p2 in sorted ouput if p2
   // has larger polar angle (in counterclockwise
   // direction) than p1
   p0 = points[0];
   qsort(&points[1], n-1, sizeof(Point), compare);

   // If two or more points make same angle with p0,
   // Remove all but the one that is farthest from p0
   // Remember that, in above sorting, our criteria was
   // to keep the farthest point at the end when more than
   // one points have same angle.
   int m = 1; // Initialize size of modified array
   for (int i=1; i<n; i++)
   {
       // Keep removing i while angle of i and i+1 is same
       // with respect to p0
       while (i < n-1 && orientation(p0, points[i],
                                    points[i+1]) == 0)
          i++;


       points[m] = points[i];
       m++;  // Update size of modified array
   }

   // If modified array of points has less than 3 points,
   // convex hull is not possible
   if (m < 3) return std::vector<Point>();

   // Create an empty stack and push first three points
   // to it.
   stack<Point> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);
   std::cout << "SIZE: " << S.size() << std::endl;

   // Process remaining n-3 points
   for (int i = 3; i < m; i++)
   {
      // Keep removing top while the angle formed by
      // points next-to-top, top, and points[i] makes
      // a non-left turn
      while (orientation(nextToTop(S), S.top(), points[i]) != 2)
         S.pop();
      S.push(points[i]);
   }

   std::vector<Point> convex_hull_edges;
   // Now stack has the output points, print contents of stack
   while (!S.empty())
   {
       Point p = S.top();
       std::cout << "(" << p.x << ", " << p.y <<")" << endl;
       convex_hull_edges.push_back(p);
       S.pop();
   }
   return convex_hull_edges;
}*/

struct Point
{
    int x, y;
};

inline bool operator==(const Point& lhs, const Point& rhs) {
	return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

struct Edge {
	Point start;
	Point end;
};

inline bool operator==(const Edge& lhs, const Edge& rhs) {
	return (((lhs.start==rhs.start) and (lhs.end == rhs.end)) or
	        ((lhs.start==rhs.end)   and (lhs.end == rhs.start)));
}

std::set<Edge> convexHullBruteForce(std::vector<Point> points) {
	std::set<Edge> result_edges;
	for (unsigned i=0; i<points.size(); ++i) {
		for (unsigned j=0; j<points.size(); ++j) {
			boost::optional<bool> same_half_plane;
			bool is_edge = true;
			//ax+by=c ,  a = y2-y1, b = x1-x2, c = x1y2 - y1x2
			double a = points[j].y - points[i].y;
			double b = points[i].x - points[j].x;
			double c = points[i].x * points[j].y - points[j].x * points[i].y;
 			for (unsigned k=0; (k<points.size()) && (k != i) && (k == j); ++k) {
				double planar = points[k].x * a + points[k].y * b - c;
				if (!same_half_plane) {
					same_half_plane = (planar > 0.0);
				}
				else if (*same_half_plane != (planar > 0.0)) {
					is_edge = false;
					break;
				}
			}
 			if (is_edge) {
 				result_edges.insert(Edge{points[i], points[j]});
 			}
		}
	}
	return result_edges;
}


void assert_algorithm_output(std::vector<Point> convex_edges) {
    assert(convex_edges[0].x == 0);
    assert(convex_edges[0].y == 3);
    assert(convex_edges[1].x == 4);
	assert(convex_edges[1].y == 4);
	assert(convex_edges[2].x == 3);
	assert(convex_edges[2].y == 1);
	assert(convex_edges[3].x == 0);
	assert(convex_edges[3].y == 0);
}


// Driver program to test above functions
int main()
{
    std::vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                                 {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    int n = sizeof(points)/sizeof(points[0]);
    auto convex_edges = convexHullBruteForce(points);
    std::cout << "Convex_edges size: " << convex_edges.size() << std::endl;
    for (Edge edge: convex_edges) {
    	std::cout << "Start: " << edge.start.x << " | " << edge.start.y << std::endl;
    	std::cout << "End: "   << edge.end.x   << " | " << edge.end.y   << std::endl;
    }
//    assert_algorithm_output(convex_edges);
    std::cout << "OK" << std::endl;
    return 0;
}
