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

		Sulock(this->screen);

		SDL_Flip(this->screen);
	}

	void Curves::add(curves::General *obj, CurveOptions *opt) {
		this->curves.push_back(pair<curves::General *, CurveOptions *> (obj, opt));
	}
}