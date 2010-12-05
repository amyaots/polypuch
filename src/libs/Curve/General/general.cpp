#include "general.hpp"

#include "cmath"

#include "../../SDL/Pixel/pixel.hpp"
using namespace sdl;

namespace curve {

	General::~General() {
		delete this->pts;
	}

	General::General() {
		this->pts = new vector<Point > ();
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
		this->pts = new vector<Point > ();
		*(this->pts) = *(obj.pts);
	}

	const General& General::operator =(const General &obj) {
		if (this->pts != obj.pts) {
			*(this->pts) = *(obj.pts);
		}
		return *this;
	}

	const bool General::operator ==(const General &obj) const {
		if(this->pts->size() < 2 || obj.pts->size() < 2) {
			return true;
		}

		Point currentStart = (*(this->pts->begin()));
		Point currentEnd = (*(this->pts->begin() + this->pts->size() - 1));

		Point objectStart = (*(obj.pts->begin()));
		Point objectEnd = (*(obj.pts->begin() + obj.pts->size() - 1));

		return (
				currentStart == objectStart &&
				currentEnd == objectEnd
				||
				currentStart == objectEnd &&
				currentEnd == objectStart
				);
	}

	//простая прямая

	void General::approximate(const Point &start, const Point &end) {
		this->pts->clear();

		Pi a = start.first;
		Pi b = start.second;

		//cout << "start = (" << a << ", " << b << ")" << endl;

		Pi c = end.first;
		Pi d = end.second;

		//cout << "end = (" << c << ", " << d << ")" << endl;

		f32 vectorX = c - a;
		f32 vectorY = d - b;

		f32 length = sqrt(vectorX * vectorX + vectorY * vectorY);

		if (length < 1) {
			this->pts->push_back(Point(a, b));
			this->pts->push_back(Point(a, b));
		} else {
			vectorX /= length;
			vectorY /= length;

			//cout << "vector = (" << vectorX << ", " << vectorY << ")" << endl;

			Pi i = 0;
			Pi currentLength = 0;
			f32 currentX = a;
			f32 currentY = b;
			while (currentLength <= length) {
				this->pts->push_back(Point((Pi) round(currentX), (Pi) round(currentY)));

				currentX += vectorX;
				currentY += vectorY;
				currentLength++;
			}
		}
	}

	void General::draw(
			SDL_Surface *screen,
			Ui32 curveColor
			) const {
		vector<Point>::const_iterator it;
		for (it = this->pts->begin(); it != this->pts->end(); it++) {
			Point current = *it;
			try {
				putpixel(screen, current.first, current.second, curveColor);
			} catch (BadPixelException &ex) {
				cerr << ex.what() << endl;
			}
		}
	}

	Point General::getStart() const {
		return *(this->pts->begin());
	}

	Point General::getEnd() const {
		return *(this->pts->begin() + this->pts->size() - 1);
	}

	Ui32 General::getSize() const {
		return this->pts->size();
	}
}