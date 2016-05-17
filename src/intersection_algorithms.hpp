#ifndef INTERSECTION_ALGORITHMS_HPP_
#define INTERSECTION_ALGORITHMS_HPP_

#include <set>
#include <iterator>
#include <map>
#include <src/primitives.hpp>

std::set<std::pair<Edge, Edge> > lineSegmentIntersectionPlaneSweep(std::vector<Edge> segments) {

	std::multimap<Point, Edge> control_points;
	for (Edge segment : segments) {
		control_points.insert(std::pair<Point, Edge>(segment.start, segment));
		control_points.insert(std::pair<Point, Edge>(segment.end, segment));
	}

	std::multimap<double, Edge> bst;
	std::set<std::pair<Edge, Edge> > intersection_result;

	for (auto& kv : control_points) {
		Point point = kv.first;
		Edge line = kv.second;

		if (point == line.start) {
			auto it = bst.emplace(std::pair<double, Edge>(line.end.y, line));
			if (it != bst.begin()) {
				auto previous_it = std::prev(it, 1);
				if (edges_intersect(line,  previous_it->second)) {
					intersection_result.emplace(std::pair<Edge, Edge>(line, previous_it->second));
				}
			}
			if (std::next(it, 1) != bst.end()) {
				auto next_it = std::next(it, 1);
				if (edges_intersect(line,  next_it->second)) {
					intersection_result.emplace(std::pair<Edge, Edge>(line,  next_it->second));
				}
			}
		}
		else if (point == line.end) {
			auto it = bst.find(point.y);
			if ( (it != bst.begin()) && (std::next(it) != bst.end())) {
				auto previous_it = std::prev(it, 1);
				auto next_it = std::next(it, 1);
				if (edges_intersect(previous_it->second, next_it->second)) {
					intersection_result.emplace(std::pair<Edge, Edge>(previous_it->second, next_it->second));
				}
				bst.erase(it);
			}
		}
		else {
			throw std::domain_error("Point does not match to start or end of the edge");
		}
	}
	return intersection_result;
}



#endif /* INTERSECTION_ALGORITHMS_HPP_ */
