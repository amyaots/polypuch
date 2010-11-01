#include "general.hpp"
#include "../../SDL/Line/line.hpp"
#include "../../SDL/Circle/circle.hpp"
using namespace sdl;

#include <cmath>

namespace segments {

	//правая или левая тройка из векторов a, b и a x b

	bool General::determinantSignum(Si16 aX, Si16 aY, Si16 bX, Si16 bY) {
		return ((aX * bY - bX * aY) >= 0);
	}

	bool General::add(const Point &a, const Point &b) {
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

		this->segments[Segment(a, b)] = so;

		return true;
	}

	bool General::add(const Segment &s) {
		this->add(s.first, s.second);
	}

	General::General(const vector<Segment> &segments) {
		vector<Segment>::const_iterator it;
		Segment currentSegment;
		for (it = segments.begin(); it != segments.end(); it++) {
			currentSegment = *it;
			this->add(currentSegment.first, currentSegment.second);
		}
	}

	void General::draw(
			SDL_Surface *screen,
			Ui32 pointColor,
			Ui16 pointRadius,
			Ui32 segmentColor,
			Ui16 segmentWidth
			) const {

		Segments::const_iterator it;
		Segment currentSegment;
		for (it = this->segments.begin(); it != this->segments.end(); it++) {
			currentSegment = it->first;
			drawLine(screen, currentSegment.first.first, currentSegment.first.second, currentSegment.second.first, currentSegment.second.second, segmentColor, segmentWidth);
			drawCircle(screen, currentSegment.first.first, currentSegment.first.second, pointColor, pointRadius);
			drawCircle(screen, currentSegment.second.first, currentSegment.second.second, pointColor, pointRadius);
		}
	}
}