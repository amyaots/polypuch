#ifndef SIMPLE_HPP
#define	SIMPLE_HPP

#include "../General/general.hpp"

namespace polygon {

    class Simple : public General {
    public:
        Simple(){}
        Simple(const vector<Point> &pts);

        bool add(const Point &p);
        virtual bool have(const Point &p) const;
    };
}

#endif
