#ifndef SEGMENTS_COMMON_HPP
#define	SEGMENTS_COMMON_HPP

#include "../../Polygon/General/general.hpp"
using namespace polygon;

#include <sstream>

namespace segments {
    
    //пересечение отрезков
    bool segmentsIntersect(
        const Point &a,
        const Point &b,
        const Point &c,
        const Point &d,
        Point &intersection
    );

    //если отрезки совпадают
    class SegmentsEquals : public exception {
    private:
        string exceptionString;

    public:
        SegmentsEquals(string);

        virtual ~SegmentsEquals() throw () {};
        virtual const char * what() const throw ();
    };

    //если передали не отрезки
    class NotSegment : public exception {
    private:
        string exceptionString;

    public:
        NotSegment(string);

        virtual ~NotSegment() throw () {};
        virtual const char * what() const throw ();
    };
}

#endif
