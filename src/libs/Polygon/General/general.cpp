#include "general.hpp"
#include "../../SDL/Circle/circle.hpp"
#include "../../SDL/Line/line.hpp"

namespace polygon {

	General::General() {
		this->pts = new vector<Point> ();
	}

	General::~General() {
		delete this->pts;
	}

	General::General(const vector<Point> &pts) {
		this->pts = new vector<Point> ();
		vector<Point>::const_iterator it;
		for (it = pts.begin(); it != pts.end(); it++) {
			vector<Point>::iterator findit;
			findit = find(this->pts->begin(), this->pts->end(), *it);
			if (findit == this->pts->end()) {
				this->pts->push_back(*it);
			}
		}
	}

	General::General(const General &obj) {
		this->pts = new vector<Point> ();
		*(this->pts) = *(obj.pts);
	}

	bool General::add(const Point &p) {
		if (find(this->pts->begin(), this->pts->end(), p) == this->pts->end()) {
			this->pts->push_back(p);
			return true;
		} else {
			return false;
		}
	}

	void General::insert(const Point &p, Pi index) {
		vector<Point>::iterator findit;
		findit = find(this->pts->begin(), this->pts->end(), p);
		if (findit == this->pts->end()) {
			this->pts->insert(this->pts->begin() + index, p);
		}
	}

	const General& General::operator =(const General &obj) {
		if (this->pts != obj.pts) {
			*(this->pts) = *(obj.pts);
		}
		return *this;
	}

	const General General::operator +(const General &obj) const {
		General result(*(this));
		vector<Point>::const_iterator it;
		for (it = obj.pts->begin(); it != obj.pts->end(); it++) {
			vector<Point>::iterator findit;
			findit = find(this->pts->begin(), this->pts->end(), *it);
			if (findit == this->pts->end()) {
				this->pts->push_back(*it);
			}
		}
		return result;
	}

	ostream & operator <<(ostream &os, const General &obj) {
		vector<Point>::const_iterator it;
		for (it = obj.pts->begin(); it != obj.pts->end(); it++) {
			os << "(" << (*it).first << ", " << (*it).second << ")" << endl;
		}
		return os;
	}

	void General::draw(
			SDL_Surface *screen,
			Ui32 pointColor,
			Ui16 pointRadius,
			Ui32 segmentColor,
			Ui16 segmentWidth,
			bool drawLines
			) const {

		if (this->pts->size() < 1) {
			return;
		}

		vector<Point>::const_iterator it;
		Point prevPoint = *(this->pts->begin());
		Point currentPoint;

		if (drawLines) {
			for (it = this->pts->begin() + 1; it != this->pts->end(); it++) {
				currentPoint = *it;
				drawLine(screen, currentPoint.first, currentPoint.second, prevPoint.first, prevPoint.second, segmentColor, segmentWidth);
				prevPoint = currentPoint;
			}
		}

		currentPoint = *(this->pts->begin());
		drawLine(screen, currentPoint.first, currentPoint.second, prevPoint.first, prevPoint.second, segmentColor, segmentWidth);
		for (it = this->pts->begin(); it != this->pts->end(); it++) {
			currentPoint = *it;
			drawCircle(screen, currentPoint.first, currentPoint.second, pointColor, pointRadius);
		}
	}

	Ui32 General::getSize() const {
		return this->pts->size();
	}
}