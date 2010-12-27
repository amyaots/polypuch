#ifndef CONVEX_HPP
#define	CONVEX_HPP

#include <boost/unordered_map.hpp>
using namespace boost;

#include "../Simple/simple.hpp"

#include "../../Render/Polygon/polygon.hpp"
using namespace render;

namespace polygon {

    typedef unordered_map<f32, Point> AnglePoint;

    enum ConvexSHellAlgo {
        GRAHAM,
        JARVIS,
        HOARE
    };

    class Convex : public Simple {
    public:

        Convex() : Simple() {
        }
        ~Convex();
        Convex(const vector<Point> &src, const ConvexSHellAlgo &algo);

        bool add(const Point &pts);
        bool have(const Point &p) const;
        bool getSegment(const Point &inside, const Point &outside, Point &start, Point &end) const;
        Convex intersect(const Convex &obj) const;

    protected:
        void graham(const vector<Point> &src);
        void jarvis(const vector<Point> &src);
        void hoare(const vector<Point> &src);
    };
}

#endif
