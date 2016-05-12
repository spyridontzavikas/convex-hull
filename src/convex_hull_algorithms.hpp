#ifndef CONVEX_HULL_ALGORITHMS_HPP
#define CONVEX_HULL_ALGORITHMS_HPP


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

std::vector<Edge> convexHullGiftWrapping(const std::vector<Point>& points) {
    std::vector<Edge> result_edges;
    Point starting_point = *(std::min(points.begin(), points.end()));
    Point start_edge = starting_point;
    bool initializing = true;
    while (initializing || start_edge != starting_point) {
        initializing = false;
        Point endpoint = points[0];
        for (unsigned i=0; i<points.size(); ++i) {
            if ((endpoint == start_edge) || (is_left_of_line(points[i], Edge(start_edge, endpoint)))) {
                endpoint = points[i];
            }
        }
        result_edges.push_back(Edge(start_edge, endpoint));
        start_edge = endpoint;
    }
    return result_edges;
}

std::vector<Edge> convexHullUpperLower(std::vector<Point>& points) {
    std::vector<Edge> result_edges;
    std::sort(points.begin(), points.end());

    std::vector<Point> upper_hull{points[0], points[1]};
    for (unsigned i=2;i<points.size(); ++i) {
        upper_hull.push_back(points[i]);
        while((upper_hull.size() > 2) &&
              is_left_of_line(*(upper_hull.end()-1), *(upper_hull.end()-3), *(upper_hull.end()-2), true)) {
            upper_hull.erase(upper_hull.end()-2);
        }
    }

    std::reverse(points.begin(), points.end());
    std::vector<Point> lower_hull{points[0], points[1]};
    for (unsigned i=2; i<points.size(); ++i) {
        lower_hull.push_back(points[i]);
        while((lower_hull.size() > 2) &&
              is_left_of_line(*(lower_hull.end()-1), *(lower_hull.end()-3), *(lower_hull.end()-2), true)) {
            lower_hull.erase(lower_hull.end()-2);
        }
    }

    for (unsigned i=1; i<lower_hull.size(); ++i) {
        upper_hull.push_back(lower_hull[i]);
    }

    Point initial_point = upper_hull[0];
    for (unsigned i=1; i<upper_hull.size(); ++i) {
        result_edges.push_back(Edge(initial_point, upper_hull[i]));
        initial_point = upper_hull[i];
    }

    return result_edges;
}


#endif // CONVEX_HULL_ALGORITHMS_HPP
