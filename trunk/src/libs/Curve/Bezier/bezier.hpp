#ifndef CURVE_BEZIER_HPP
#define	CURVE_BEZIER_HPP

#include "../../Curve/General/general.hpp"

namespace curve {

    class Bezier : public General {
    protected:
        vector<Point> controlPoints;

    public:

        Bezier() : General() {
        }

        void approximate(const vector<Point> &controlPoints);

        Point getPoint(f32 t) const;
    };
}

#endif