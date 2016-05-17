#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include <iostream>
#include <cmath>

struct Point
{
    double x, y;
};

inline bool operator==(const Point& lhs, const Point& rhs) {
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

inline bool operator!=(const Point& lhs, const Point& rhs) {
    return not operator==(lhs, rhs);
}

inline bool operator<(const Point& lhs, const Point& rhs) {
    return ( (lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y));
}

inline bool operator>(const Point& lhs, const Point& rhs) {
    return ( (lhs.x > rhs.x) || (lhs.x == rhs.x && lhs.y > rhs.y));
}

inline std::ostream& operator<<(std::ostream& stream, const Point& point) {
    stream << point.x << ", " << point.y;
    return stream;
}

enum class rotation { COLINEAR, CLOCKWISE, COUNTERCLOCKWISE };

struct Edge {
    Edge(Point start, Point end)
        : start{start}
        , end{end}
    {
    	normalize();
    }
    Point start;
    Point end;

    void normalize() {
    	if (start > end) {
    		Point temp = start;
    		start = end;
    		end = temp;
    	}
    }
    bool is_point_on_edge(const Point& point) const {
        return (point.x <= std::max(start.x, end.x) && point.x >= std::min(start.x, end.x) &&
                point.y <= std::max(start.y, end.y) && point.y >= std::min(start.y, end.y));
    }

    rotation point_edge_rotation(const Point& point_to_check) const {
        double a = end.y - start.y;
        double b = end.x - start.x;
        double c = start.x * end.y - end.x * start.y;
        double eq_result = (a * point_to_check.x - b * point_to_check.y - c);

        if (std::abs(eq_result) <= 0.00001) return rotation::COLINEAR;
        else if (eq_result > 0.00001)      return rotation::CLOCKWISE;
        else                               return rotation::COUNTERCLOCKWISE;
    }

};

inline bool operator==(const Edge& lhs, const Edge& rhs) {
    return (((lhs.start==rhs.start) and (lhs.end == rhs.end)) or
            ((lhs.start==rhs.end)   and (lhs.end == rhs.start)));
}

inline std::ostream& operator<<(std::ostream& stream, const Edge& edge) {
    stream << edge.start << ", " << edge.end;
    return stream;
}

inline bool operator<(const Edge& lhs, const Edge& rhs) {
    return (lhs.start.x < rhs.start.x);
}

bool is_left_of_line(const Point& point_to_check, const Point& line_start, const Point& line_end, bool accept_colinear=false) {
    if (accept_colinear)
    	return (Edge(line_start, line_end).point_edge_rotation(point_to_check) != rotation::CLOCKWISE);
    else
    	return (Edge(line_start, line_end).point_edge_rotation(point_to_check) != rotation::COUNTERCLOCKWISE);
}

bool edges_intersect(const Edge& edge1, const Edge& edge2) {
    rotation o1 = edge1.point_edge_rotation(edge2.start);
    rotation o2 = edge1.point_edge_rotation(edge2.end);
    rotation o3 = edge2.point_edge_rotation(edge1.start);
    rotation o4 = edge2.point_edge_rotation(edge1.end);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == rotation::COLINEAR && edge1.is_point_on_edge(edge2.start)) return true;
    if (o2 == rotation::COLINEAR && edge1.is_point_on_edge(edge2.end))   return true;
    if (o3 == rotation::COLINEAR && edge2.is_point_on_edge(edge1.start)) return true;
    if (o4 == rotation::COLINEAR && edge2.is_point_on_edge(edge1.end))   return true;
    return false;
}

#endif // PRIMITIVES_HPP
