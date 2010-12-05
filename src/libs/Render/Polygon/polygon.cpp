#include <iostream>
#include <sstream>
using namespace std;

#include "polygon.hpp"
#include "../../SDL/Line/line.hpp"
#include "../../SDL/Circle/circle.hpp"

namespace render {

	Polygon::~Polygon() {
		this->~General();
	}

	void Polygon::reDraw() const {
		Slock(this->screen);

		DrawSurface(this->screen, this->back, 0, 0, 0, 0, this->back->w, this->back->h);

		vector<pair<polygon::General *, PolygonOptions *> >::const_iterator it;
		pair<polygon::General *, PolygonOptions *> currentPair;
		for (it = this->polygons.begin(); it != this->polygons.end(); it++) {
			currentPair = *it;
			if (currentPair.first) {
				currentPair.first->draw(
						this->screen,
						currentPair.second->pointColor,
						currentPair.second->pointRadius,
						currentPair.second->segmentColor,
						currentPair.second->segmentWidth,
						currentPair.second->drawLines
						);
			}
		}

		vector<pair<polygon::Point *, PointOptions *> >::const_iterator jt;
		pair<polygon::Point *, PointOptions *> currentPointPair;
		for (jt = this->points.begin(); jt != this->points.end(); jt++) {
			currentPointPair = *jt;
			if (currentPointPair.first) {
				drawCircle(
						this->screen,
						currentPointPair.first->first,
						currentPointPair.first->second,
						currentPointPair.second->pointColor,
						currentPointPair.second->pointRadius
						);
			}
		}

		Sulock(this->screen);

		SDL_Flip(this->screen);
	}

	void Polygon::add(polygon::General *obj, PolygonOptions *opt) {
		this->polygons.push_back(pair<polygon::General *, PolygonOptions *> (obj, opt));
	}

	void Polygon::add(polygon::Point *p, PointOptions *opt) {
		this->points.push_back(pair<polygon::Point *, PointOptions *> (p, opt));
	}
}