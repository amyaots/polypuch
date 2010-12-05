#include "ermit.hpp"

#include "cmath"

#include "../../SDL/Pixel/pixel.hpp"
using namespace sdl;

namespace curve {

	Ermit::~Ermit() {
		this->~General();
	}

	inline double getAlpha(double t) {
		return 1 - 3 * t * t + 2 * t * t * t;
	}

	inline double getBeta(double t) {
		return 3 * t * t - 2 * t * t * t;
	}

	inline double getGamma(double t) {
		return t - 2 * t * t + t * t * t;
	}

	inline double getDelta(double t) {
		return -t * t + t * t * t;
	}

	//кривая эрмита

	void Ermit::approximate(
			const Point &start,
			const Point &end,
			const Point &startDirection,
			const Point &endDirection,
			Pi maxLength
			) {

		this->pts->clear();

		Pi startX = start.first;
		Pi startY = start.second;

		Pi endX = end.first;
		Pi endY = end.second;

		//бегает от 0 до 1
		f32 t = 0;
		f32 step = 1.0 / (maxLength);

		while (t <= 1) {
			Point currentPoint;

			currentPoint.first = round(getAlpha(t) * startX + getBeta(t) * endX + getGamma(t) * startDirection.first + getDelta(t) * endDirection.first);
			currentPoint.second = round(getAlpha(t) * startY + getBeta(t) * endY + getGamma(t) * startDirection.second + getDelta(t) * endDirection.second);

			vector<Point>::const_iterator it;
			Ui32 k;
			Ui32 size = this->pts->size();
			bool add = true;
			for (k = 0, it = this->pts->begin() + size - 1; k < size; it--, k++) {
				if (*it == currentPoint) {
					add = false;
					break;
				}
			}

			if (add) {
				this->pts->push_back(currentPoint);
			}
			t += step;
		}
	}
}