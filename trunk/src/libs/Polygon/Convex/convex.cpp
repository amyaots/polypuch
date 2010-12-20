#include "convex.hpp"

namespace polygon {

    Convex::Convex(const vector<Point> &src, const ConvexSHellAlgo &algo) {
		switch(algo) {
			case GRAHAM:
				this->graham(src);
				break;

			case JARVIS:
				this->jarvis(src);
				break;
		}
    }

    Convex::~Convex() {
        this->~Simple();
    }
}