#ifndef INTERSECTION_ALGORITHMS_HPP_
#define INTERSECTION_ALGORITHMS_HPP_

#include <set>
#include <iterator>
#include <map>
#include <src/primitives.hpp>

namespace line_segment_intersection {

namespace detail {

	void check_intersection_and_update(const Edge& line1, const Edge& line2, std::set<std::pair<Edge, Edge>>& result) {
		if (edges_intersect(line1,  line2))
			result.emplace(std::pair<Edge, Edge>(line1, line2));
	}

	void handle_starting_point(std::multimap<double, Edge>& bst, const Edge& line, std::set<std::pair<Edge, Edge>>& result) {
		//Start of a segment, adding to BSTree and checking for intersections with tree neighbors.
		auto it = bst.emplace(std::pair<double, Edge>(line.end.y, line));
		if (it != bst.begin()) {
			auto previous_it = std::prev(it, 1);
			check_intersection_and_update(line, previous_it->second, result);
		}
		if (std::next(it, 1) != bst.end()) {
			auto next_it = std::next(it, 1);
			check_intersection_and_update(line, next_it->second, result);
		}
	}

	void handle_ending_point(std::multimap<double, Edge>& bst, const Edge& line, std::set<std::pair<Edge, Edge>>& result) {
		//Erase segment from tree, check if tree neighbors intersect
		auto it = bst.find(line.end.y);
		if (it == bst.end()) {
			throw std::domain_error("Segment was not inserted to BST.");
		}
		if ( (it != bst.begin()) && (std::next(it) != bst.end())) {
			auto previous_it = std::prev(it, 1);
			auto next_it = std::next(it, 1);
			check_intersection_and_update(previous_it->second, next_it->second, result);
			bst.erase(it);
		}
	}

} //namespace detail


std::set<std::pair<Edge, Edge> > lineSegmentIntersectionPlaneSweep(std::vector<Edge> segments) {
	//Sorting elements on x axis, since multimap sorts the elements automatically
	std::multimap<Point, Edge> control_points;
	for (Edge segment : segments) {
		control_points.insert(std::pair<Point, Edge>(segment.start, segment));
		control_points.insert(std::pair<Point, Edge>(segment.end, segment));
	}
	//Horrid hack, using a multimap as a BST (uses an RBTree underneath, should be ok from a complexity perspective)
	std::multimap<double, Edge> bst;
	std::set<std::pair<Edge, Edge> > intersection_result;

	for (auto& kv : control_points) {
		Point point = kv.first;
		Edge line = kv.second;
		if (point == line.start) {
			detail::handle_starting_point(bst, line, intersection_result);
		}
		else if (point == line.end) {
			detail::handle_ending_point(bst, line, intersection_result);
		}
		else {
			throw std::domain_error("Point does not match to start or end of the edge");
		}
	}
	return intersection_result;
}

} // namespace line_segment_intersection


#endif /* INTERSECTION_ALGORITHMS_HPP_ */
