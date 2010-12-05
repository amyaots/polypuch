#include <iostream>
#include <sstream>
using namespace std;

#include "segments.hpp"
#include "../../SDL/Line/line.hpp"
#include "../../SDL/Circle/circle.hpp"

namespace render {

	Segments::~Segments() {
		this->~General();
	}

	void Segments::reDraw() const {
		Slock(this->screen);

		DrawSurface(this->screen, this->back, 0, 0, 0, 0, this->back->w, this->back->h);

		vector<pair<segments::General *, SegmentsOptions *> >::const_iterator kt;
		pair<segments::General *, SegmentsOptions *> currentSegmentsPair;
		for (kt = this->segments.begin(); kt != this->segments.end(); kt++) {
			currentSegmentsPair = *kt;
			if (currentSegmentsPair.first) {
				currentSegmentsPair.first->draw(
						this->screen,
						currentSegmentsPair.second->pointColor,
						currentSegmentsPair.second->pointRadius,
						currentSegmentsPair.second->segmentColor,
						currentSegmentsPair.second->segmentWidth
						);
			}
		}

		Sulock(this->screen);

		SDL_Flip(this->screen);
	}

	void Segments::add(segments::General *s, SegmentsOptions *opt) {
		this->segments.push_back(pair<segments::General *, SegmentsOptions *> (s, opt));
	}
}