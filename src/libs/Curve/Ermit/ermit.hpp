#ifndef CURVE_ERMIT_HPP
#define	CURVE_ERMIT_HPP

#include "../../Curve/General/general.hpp"

namespace curve {

    class Ermit : public General {
    public:

        Ermit() : General() {}

        void approximate(
                const Point &start,
                const Point &end,
                const Point &startDirection,
                const Point &endDirection,
                Pi maxLength
                );
    };
}

#endif