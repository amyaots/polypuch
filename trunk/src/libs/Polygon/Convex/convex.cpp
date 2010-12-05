#include "convex.hpp"

namespace polygon {

    Convex::Convex(const vector<Point> &src) {
        this->graham(src);
    }

    Convex::~Convex() {
        this->~Simple();
    }
}