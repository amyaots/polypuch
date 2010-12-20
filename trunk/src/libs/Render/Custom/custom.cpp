#include <iostream>
#include <algorithm>
using namespace std;

#include "custom.hpp"
#include "../../SDL/Line/line.hpp"
#include "../../SDL/Circle/circle.hpp"

#include "../../../examples/GeneralCurvesBezierFire/Sonne/Sonne.hpp"

namespace render {

	Custom::~Custom() {
		this->~General();
	}

	void Custom::reDraw() const {
		Slock(this->screen);

		DrawSurface(this->screen, this->back, 0, 0, 0, 0, this->back->w, this->back->h);

		vector<AbstractRenderObject *>::const_iterator it;
		AbstractRenderObject *currentObject;
		for (it = this->objects.begin(); it != this->objects.end(); it++) {
			currentObject = *it;
			currentObject->draw(this->screen);
		}

		Sulock(this->screen);

		SDL_Flip(this->screen);
	}

	void Custom::add(AbstractRenderObject* obj) {
		this->objects.push_back(obj);
	}

	void Custom::remove(AbstractRenderObject* obj) {
		vector<AbstractRenderObject *>::iterator find_it;
		find_it = find(this->objects.begin(), this->objects.end(), obj);
		if (find_it != this->objects.end()) {
			this->objects.erase(find_it);
		}
	}
}