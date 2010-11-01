#include "convex.hpp"

namespace polygon {

	Convex::Convex(const vector<Point> &src) {
		this->pts = new vector<Point>;
		this->graham(src);
	}
}