#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include <iostream>

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

inline std::ostream& operator<<(std::ostream& stream, const Point& point) {
    stream << point.x << ", " << point.y;
    return stream;
}

struct Edge {
    Edge(Point start, Point end)
        : start{start}
        , end{end}
    {}
    Point start;
    Point end;
};

inline bool operator==(const Edge& lhs, const Edge& rhs) {
    return (((lhs.start==rhs.start) and (lhs.end == rhs.end)) or
            ((lhs.start==rhs.end)   and (lhs.end == rhs.start)));
}

inline std::ostream& operator<<(std::ostream& stream, const Edge& edge) {
    stream << edge.start << ", " << edge.end;
    return stream;
}

bool is_left_of_line(const Point& point_to_check, const Edge& reference, bool accept_colinear=false) {
    double a = reference.end.y - reference.start.y;
    double b = reference.end.x - reference.start.x;
    double c = reference.start.x * reference.end.y - reference.end.x * reference.start.y;
    double eq_result = (a * point_to_check.x - b * point_to_check.y - c);
    if(accept_colinear)
        return eq_result < 0.0001;
    else
        return eq_result < 0.0;
}

bool is_left_of_line(Point point_to_check, Point line_start, Point line_end, bool accept_colinear=false) {
    return is_left_of_line(point_to_check, Edge(line_start, line_end), accept_colinear);
}


#endif // PRIMITIVES_HPP
