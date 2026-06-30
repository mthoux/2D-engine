    #include "CollisionSystem.hpp"

    bool CollisionSystem2::isOverlaping(const Shape& shape1, const Shape& shape2) {
        std::vector<Vec2f> axes1 = shape1.getAxes();
        std::vector<Vec2f> axes2 = shape2.getAxes();

        for(int i = 0; i < axes1.size(); i++) {
            Vec2f axis = axes1[i];
            Vec2f p1 = shape1.project(axis);
            Vec2f p2 = shape2.project(axis);

            if (p1.y < p2.x || p2.y < p1.x) {
                return false;
            }
        }

        for(int i = 0; i < axes2.size(); i++) {
            Vec2f axis = axes2[i];
            Vec2f p1 = shape1.project(axis);
            Vec2f p2 = shape2.project(axis);

            if (p1.y < p2.x || p2.y < p1.x) {
                return false;
            }
        }

        return true;
    }

    std::optional<Vec2f> CollisionSystem2::getMTV(const Shape& shape1, const Shape& shape2) {
        double min_overlap = std::numeric_limits<double>::infinity();
        Vec2f min_axis;

        std::vector<Vec2f> axes1 = shape1.getAxes();
        std::vector<Vec2f> axes2 = shape2.getAxes();

        for(int i = 0; i < axes1.size(); i++) {
            Vec2f axis = axes1[i];
            Vec2f p1 = shape1.project(axis);
            Vec2f p2 = shape2.project(axis);

            if (p1.y < p2.x || p2.y < p1.x) {
                return std::nullopt;
            }
            else {

                // Get the overlap 
                double overlap = std::min(p1.y, p2.y) - std::max(p1.x, p2.x);

                // Check for containment 
                if ((p1.x <= p2.x && p1.y >= p2.y) || (p2.x <= p1.x && p2.y >= p1.y)) {
                    double mins = abs(p1.x - p2.x);
                    double maxs = abs(p1.y - p2.y);

                    if (mins < maxs) overlap += mins;
                    else overlap += maxs;
                }

                if (overlap < min_overlap) {
                    min_overlap = overlap;
                    min_axis = axis;
                }
            }
        }

        for(int i = 0; i < axes2.size(); i++) {
            Vec2f axis = axes2[i];
            Vec2f p1 = shape1.project(axis);
            Vec2f p2 = shape2.project(axis);

            if (p1.y < p2.x || p2.y < p1.x) {
                return std::nullopt;
            }
            else {

                // Get the overlap
                double overlap = std::min(p1.y, p2.y) - std::max(p1.x, p2.x);
                
                // Check for containment 
                if ((p1.x <= p2.x && p1.y >= p2.y) || (p2.x <= p1.x && p2.y >= p1.y)) {
                    double mins = abs(p1.x - p2.x);
                    double maxs = abs(p1.y - p2.y);

                    if (mins < maxs) overlap += mins;
                    else overlap += maxs;
                }

                if (overlap < min_overlap) {
                    min_overlap = overlap;
                    min_axis = axis;
                }
            }
        }

        Vec2f deltaCenters = shape2.getCenter() - shape1.getCenter();
        if (deltaCenters.dot(min_axis) < 0) {
            min_axis = -min_axis;
        }

        Vec2f mtv = min_axis.normalized() * min_overlap;
        return mtv;
    }


