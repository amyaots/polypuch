#ifndef SEGMENTS_SIMPLE_HPP
#define	SEGMENTS_SIMPLE_HPP

#include "../Common/common.hpp"
#include "../General/general.hpp"

namespace segments {
    
    class Simple : public General {
    public:

        Simple() {
        }
        Simple(const vector<Segment> &);

        bool add(const Point &a, const Point &b);
        bool add(const Segment &s);
    };
}

#endif
