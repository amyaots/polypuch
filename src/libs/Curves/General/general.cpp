#include "general.hpp"

#include "../../SDL/Circle/circle.hpp"
using namespace sdl;

namespace curves {

	General::General() {
		this->curves = new vector<curve::General>();
	}

	General::~General() {
		delete this->curves;
	}

	General::General(const vector<curve::General> &curves) {
		this->curves = new vector<curve::General>();
		vector<curve::General>::const_iterator it;
		for (it = curves.begin(); it != curves.end(); it++) {
			vector<curve::General>::iterator findit;
			findit = find(this->curves->begin(), this->curves->end(), *it);
			if (findit == this->curves->end()) {
				this->curves->push_back(*it);
			}
		}
	}

	General::General(const General &obj) {
		this->curves = new vector<curve::General>();
		*(this->curves) = *(obj.curves);
	}

	Ui32 General::getSize() const {
		return this->curves->size();
	}

	bool General::add(const Curve &p) {

		if (find(this->curves->begin(), this->curves->end(), p) == this->curves->end()) {
			this->curves->push_back(p);
			return true;
		} else {
			return false;
		}
	}

	void General::insert(const Curve &p, Pi index) {
		vector<curve::General>::iterator findit;
		findit = find(this->curves->begin(), this->curves->end(), p);
		if (findit == this->curves->end()) {
			this->curves->insert(this->curves->begin() + index, p);
		}
	}

	const General& General::operator =(const General &obj) {
		if (this->curves != obj.curves) {
			*(this->curves) = *(obj.curves);
		}
		return *this;
	}

	const General General::operator +(const General &obj) const {
		General result(*(this));
		vector<curve::General>::const_iterator it;
		for (it = obj.curves->begin(); it != obj.curves->end(); it++) {
			vector<curve::General>::iterator findit;
			findit = find(this->curves->begin(), this->curves->end(), *it);
			if (findit == this->curves->end()) {
				this->curves->push_back(*it);
			}
		}
		return result;
	}

	void General::draw(
			SDL_Surface *screen,
			Ui32 pointColor,
			Ui16 pointRadius,
			Ui32 curveColor
			) const {
		vector<curve::General>::const_iterator it;
		for(it = this->curves->begin(); it != this->curves->end(); it++) {
			Curve current = *it;
			Point startPoint = current.getStart();
			Point endPoint = current.getEnd();

			current.draw(screen, curveColor);
			drawCircle(screen, startPoint.first, startPoint.second, pointColor, pointRadius);
			drawCircle(screen, endPoint.first, endPoint.second, pointColor, pointRadius);
		}
	}
}