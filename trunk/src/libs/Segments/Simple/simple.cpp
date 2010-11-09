#include "simple.hpp"
using namespace sdl;

namespace segments {

	bool Simple::add(const Point &a, const Point &b) {
		Si16 vX = b.first - a.first;
		Si16 vY = b.second - a.second;
		f32 vLength = sqrt(vX * vX + vY * vY);

		SegmentOptions so;
		so.dirVector.first = (f32) vX / vLength;
		so.dirVector.second = (f32) vY / vLength;

		//определитель
		//  a b >= 0
		// -b a
		//тогда как
		// a  b <= 0
		// b -a

		so.dirVectorOrt.first = -so.dirVector.second;
		so.dirVectorOrt.second = so.dirVector.first;

		Segments::const_iterator it;
		FullSegment currentSegment;
		Point intersection;
		for(it = this->segments.begin(); it != this->segments.end(); it++) {
			currentSegment = *it;
			if(segmentsIntersect(a, b, currentSegment.first.first, currentSegment.first.second, intersection)) {
				return false;
			}
		}

		this->segments[Segment(a, b)] = so;
		
		return true;
	}

	bool Simple::add(const Segment &s) {
		this->add(s.first, s.second);
	}

	Simple::Simple(const vector<Segment> &segments) {
		vector<Segment>::const_iterator it;
		Segment currentSegment;
		for (it = segments.begin(); it != segments.end(); it++) {
			currentSegment = *it;
			this->add(currentSegment.first, currentSegment.second);
		}
	}
}