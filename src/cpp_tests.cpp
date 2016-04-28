// A C++ program to find convex hull of a set of points. Refer
// http://www.geeksforgeeks.org/orientation-3-ordered-points/
// for explanation of orientation()
#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <stdlib.h>
#include <boost/optional.hpp>


struct Point
{
    double x, y;
};

inline bool operator==(const Point& lhs, const Point& rhs) {
	return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

inline bool operator<(const Point& lhs, const Point& rhs) {
	return (lhs.x < rhs.x);
}

struct Edge {
	Point start;
	Point end;
};

inline bool operator==(const Edge& lhs, const Edge& rhs) {
	return (((lhs.start==rhs.start) and (lhs.end == rhs.end)) or
	        ((lhs.start==rhs.end)   and (lhs.end == rhs.start)));
}

std::vector<Edge> convexHullBruteForce(std::vector<Point> points) {
	std::vector<Edge> result_edges;
	for (unsigned i=0; i<points.size(); ++i) {
		for (unsigned j=i; j<points.size(); ++j) {
			if (i==j) continue;
			boost::optional<bool> same_half_plane;
			bool is_edge = true;
			//ax+by=c ,  a = y2-y1, b = x1-x2, c = x1y2 - y1x2
			double a = points[j].y - points[i].y;
			double b = points[i].x - points[j].x;
			double c = points[i].x * points[j].y - points[j].x * points[i].y;
 			for (unsigned k=0; k<points.size(); ++k) {
 				if ((i==k) || (j==k)) continue;
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
  				result_edges.push_back(Edge{points[i], points[j]});
 			}
		}
	}
	return result_edges;
}
/*
jarvis(S)
   pointOnHull = leftmost point in S
   i = 0
   repeat
      P[i] = pointOnHull
      endpoint = S[0]         // initial endpoint for a candidate edge on the hull
      for j from 1 to |S|
         if (endpoint == pointOnHull) or (S[j] is on left of line from P[i] to endpoint)
            endpoint = S[j]   // found greater left turn, update endpoint
      i = i+1
      pointOnHull = endpoint
   until endpoint == P[0]      // wrapped around to first hull point*/

std::vector<Edge> convexHullGiftWrapping(std::vector<Point> points) {
	std::vector<Edge> result_edges;
	Point starting_point = std::min(points.begin(), points.end());
	Point current_edge_start = starting_point;
	for (unsigned i=0; i<points.size(); ++i) {

	}


	return result_edges;
}

void assert_algorithm_output(std::vector<Edge> convex_edges) {
	Edge one{Point{0,3}, Point{4,4}};
	assert(std::find(convex_edges.begin(), convex_edges.end(), one) != convex_edges.end());
	Edge two{Point{0,3}, Point{0,0}};
	assert(std::find(convex_edges.begin(), convex_edges.end(), two) != convex_edges.end());
	Edge three{Point{3,1}, Point{4,4}};
	assert(std::find(convex_edges.begin(), convex_edges.end(), three) != convex_edges.end());
	Edge four{Point{0,0}, Point{3,1}};
	assert(std::find(convex_edges.begin(), convex_edges.end(), four) != convex_edges.end());
}

int main()
{
    std::vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                                 {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    auto convex_edges = convexHullBruteForce(points);
    std::cout << "Convex_edges size: " << convex_edges.size() << std::endl;
    for (Edge edge: convex_edges) {
    	std::cout << "Start: " << edge.start.x << " | " << edge.start.y << std::endl;
    	std::cout << "End: "   << edge.end.x   << " | " << edge.end.y   << std::endl;
    }
    assert_algorithm_output(convex_edges);
    std::cout << "OK" << std::endl;
    return 0;
}
