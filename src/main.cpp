#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <stdlib.h>
#include <boost/optional.hpp>
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
    std::cout << "No assert was triggered." << std::endl;
    return 0;
}
