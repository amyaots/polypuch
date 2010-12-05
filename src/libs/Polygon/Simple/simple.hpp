#ifndef SIMPLE_HPP
#define	SIMPLE_HPP

#include "../General/general.hpp"

namespace polygon {

    class Simple : public General {
    public:
        Simple() : General() {}
        ~Simple();
        Simple(const vector<Point> &pts) : General(pts) {}

        bool add(const Point &p);
        bool have(const Point &p) const;
    };
}

#endif
