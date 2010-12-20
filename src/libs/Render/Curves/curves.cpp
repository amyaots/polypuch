#include <iostream>
#include <sstream>
using namespace std;

#include "curves.hpp"
#include "../../SDL/Line/line.hpp"
#include "../../SDL/Circle/circle.hpp"

namespace render {

	Curves::~Curves() {
		this->~General();
	}

	void Curves::reDraw() const {
		Slock(this->screen);

		DrawSurface(this->screen, this->back, 0, 0, 0, 0, this->back->w, this->back->h);

		vector<pair<curves::General *, CurveOptions *> >::const_iterator it;
		pair<curves::General *, CurveOptions *> currentPair;
		for (it = this->curves.begin(); it != this->curves.end(); it++) {
			currentPair = *it;
			if (currentPair.first) {
				currentPair.first->draw(
						this->screen,
						currentPair.second->pointColor,
						currentPair.second->pointRadius,
						currentPair.second->curveColor
						);
			}
		}

		vector<pair<polygon::Point, PointOptions *> >::const_iterator jt;
		pair<polygon::Point, PointOptions *> currentPointPair;
		for (jt = this->points.begin(); jt != this->points.end(); jt++) {
			currentPointPair = *jt;
			drawCircle(
					this->screen,
					currentPointPair.first.first,
					currentPointPair.first.second,
					currentPointPair.second->pointColor,
					currentPointPair.second->pointRadius
					);
		}

		Sulock(this->screen);

		SDL_Flip(this->screen);
	}

	void Curves::add(curves::General *obj, CurveOptions *opt) {
		this->curves.push_back(pair<curves::General *, CurveOptions *> (obj, opt));
	}

	void Curves::add(polygon::Point p, PointOptions *opt) {
		this->points.push_back(pair<polygon::Point, PointOptions *> (p, opt));
	}
}