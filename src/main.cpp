#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <stdlib.h>
#include <src/primitives.hpp>
#include <src/convex_hull_algorithms.hpp>


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
    std::vector<Point> points = {{4, 4}, {0, 3}, {1, 1}, {2, 2},
                                 {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    auto convex_brute_edges = convexHullBruteForce(points);
    assert_algorithm_output(convex_brute_edges);
    auto convex_gift_edges = convexHullGiftWrapping(points);
    assert_algorithm_output(convex_gift_edges);
    auto convex_upper_lower_edges = convexHullUpperLower(points);
    assert_algorithm_output(convex_upper_lower_edges);


    /*//change N = 4
    Point p[] = { { 1, 6, 0, 1 }, { 2, 9, 1, 1 }, { 9, 8, 2, 1 }, { 10, 2, 3, 1 } };
    Point q[] = { { 6, 6, 0, 0 }, { 15, 2, 1, 0 }, { 14, 8, 2, 0 }, { 13, 2, 3, 0 } };*/
    std::vector<Edge> line_segments{ { Point{1, 6}, Point{0, 1} }, { Point{2, 9}, Point{1, 1} },
    	                             { Point{9, 8}, Point{2, 1} }, { Point{10, 2}, Point{3, 1} },
									 { Point{6, 6}, Point{0, 0} }, { Point{15, 2}, Point{1, 0} },
									 { Point{14, 8}, Point{2, 0} }, { Point{13, 2}, Point{3, 0} } };

    std::cout << "No assert was triggered." << std::endl;
    return 0;
}
