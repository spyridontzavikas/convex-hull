#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <stack>
#include <stdlib.h>
#include <src/primitives.hpp>
#include <src/convex_hull_algorithms.hpp>
#include <src/intersection_algorithms.hpp>
#include <src/art_gallery.hpp>


void assert_convex_hull_output(std::vector<Edge> convex_edges) {
	Edge one{Point{0,3}, Point{4,4}};
	assert(std::find(convex_edges.begin(), convex_edges.end(), one) != convex_edges.end());
	Edge two{Point{0,3}, Point{0,0}};
	assert(std::find(convex_edges.begin(), convex_edges.end(), two) != convex_edges.end());
    Edge three{Point{3,1}, Point{4,4}};
	assert(std::find(convex_edges.begin(), convex_edges.end(), three) != convex_edges.end());
	Edge four{Point{0,0}, Point{3,1}};
	assert(std::find(convex_edges.begin(), convex_edges.end(), four) != convex_edges.end());
}

void assert_line_segment_intersection_output(std::set<std::pair<Edge, Edge>> intersections) {
	assert(intersections.size() == 2);
	std::pair<Edge, Edge> one { { Point{3, 0}, Point{13, 2} }, { Point{1, 0}, Point{15, 2} } };
	assert(std::find(intersections.begin(), intersections.end(), one) != intersections.end());
	std::pair<Edge, Edge> two { { Point{3, 1}, Point{10, 2} }, { Point{2, 0}, Point{14, 8} } };
	assert(std::find(intersections.begin(), intersections.end(), two) != intersections.end());
}

int main()
{
    std::vector<Point> points = {{4, 4}, {0, 3}, {1, 1}, {2, 2},
                                 {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    auto convex_brute_edges = convexHullBruteForce(points);
    assert_convex_hull_output(convex_brute_edges);
    auto convex_gift_edges = convexHullGiftWrapping(points);
    assert_convex_hull_output(convex_gift_edges);
    auto convex_upper_lower_edges = convexHullUpperLower(points);
    assert_convex_hull_output(convex_upper_lower_edges);

    std::vector<Edge> line_segments{ { Point{0, 1}, Point{1, 6}  }, { Point{1, 1}, Point{2, 9}  },
    	                             { Point{2, 1}, Point{9, 8}  }, { Point{3, 1}, Point{10, 2} },
									 { Point{0, 0}, Point{6, 6}  }, { Point{1, 0}, Point{15, 2} },
									 { Point{2, 0}, Point{14, 8} }, { Point{3, 0}, Point{13, 2} } };

    std::set<std::pair<Edge, Edge> > intersections = line_segment_intersection::lineSegmentIntersectionPlaneSweep(line_segments);
    assert_line_segment_intersection_output(intersections);

//    std::vector<Edge> polygon { { Point{0, 0},  Point{3, 2}  }, { Point{3, 2},  Point{6, 2}  },
//							    { Point{6, 2},  Point{8, -1} }, { Point{8, -1}, Point{7, -4} },
//							    { Point{7, -4}, Point{3, -3} }, { Point{3, -3}, Point{3, 0}  },
//							    { Point{3, 0},  Point{0, 0} } };
//    std::set<Point> polygon { Point{0, 0},  Point{3, 2}, Point{6, 2},  Point{8, -1}, Point{7, -4}, Point{3, -3}, Point{3, 0} };
//    polygonTriangulation(polygon);
    std::cout << "No assert was triggered." << std::endl;
    return 0;
}
