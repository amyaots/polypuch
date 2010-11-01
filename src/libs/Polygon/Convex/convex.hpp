#ifndef CONVEX_HPP
#define	CONVEX_HPP

#include "../Simple/simple.hpp"

#include "../../Render/Polygon/polygon.hpp"
using namespace render;

namespace polygon {

    class Convex : public Simple {
    public:
        Convex(){}
        Convex(const vector<Point> &src);

        bool add(const Point &pts);
        bool have(const Point &p) const;

    private:
        //для грехема и локализации
        inline static f32 getAngle(Point from, Point to);
        inline static bool determinantSignum(const Point &a, const Point &b, const Point &c);
        void graham(const vector<Point> &src);
    };
}

#endif
