#ifndef CONVEX_HPP
#define	CONVEX_HPP

#include <boost/unordered_map.hpp>
using namespace boost;

#include "../Simple/simple.hpp"

#include "../../Render/Polygon/polygon.hpp"
using namespace render;

namespace polygon {

    typedef unordered_map<f32, Point> AnglePoint;

    class Convex : public Simple {
    public:

        Convex() : Simple() {
        }
        ~Convex();
        Convex(const vector<Point> &src);

        bool add(const Point &pts);
        bool have(const Point &p) const;

    protected:
        void graham(const vector<Point> &src);
    };
}

#endif
