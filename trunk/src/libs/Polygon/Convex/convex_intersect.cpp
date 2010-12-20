#include "convex.hpp"
#include "../../Segments/Common/common.hpp"
using namespace segments;

namespace polygon {

	Convex Convex::intersect(const Convex &obj) const {
		vector<Point> result;

		Point currentPoint;
		
		vector<Point>::const_iterator it;

		for (it = obj.pts->begin(); it != obj.pts->end(); it++) {
			currentPoint = *it;
			if(this->have(currentPoint)) {
				result.push_back(currentPoint);
			}
		}

		for (it = this->pts->begin(); it != this->pts->end(); it++) {
			currentPoint = *it;
			if(obj.have(currentPoint)) {
				result.push_back(currentPoint);
			}
		}

		Point startPointI, endPointI;
		Point startPointJ, endPointJ;
		Point intersection;

		vector<Point>::const_iterator jt;

		size_t lastIndexI = obj.pts->size() - 1;
		size_t lastIndexJ = this->pts->size() - 1;
		
		startPointI = *(obj.pts->begin() + lastIndexI);
		for (it = obj.pts->begin(); it != obj.pts->end(); it++) {
			endPointI = *it;

			startPointJ = *(this->pts->begin() + lastIndexJ);
			for (jt = this->pts->begin(); jt != this->pts->end(); jt++) {
				endPointJ = *jt;

				if(segmentsIntersect(startPointI, endPointI, startPointJ, endPointJ, intersection)) {
					result.push_back(intersection);
				}

				startPointJ = endPointJ;
			}
			startPointI = endPointI;
		}

		return Convex(result, GRAHAM);
	}
}