#include "ermit.hpp"

#include <cmath>

#include "../../SDL/Pixel/pixel.hpp"
using namespace sdl;

namespace curve {

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
		this->pts->push_back(start);

		Pi startX = start.first;
		Pi startY = start.second;

		Pi endX = end.first;
		Pi endY = end.second;

		//бегает от 0 до 1
		f32 t = 0;
		f32 step = 1.0 / (maxLength);

		while (t <= 1) {
			Point currentPoint;
			t += step;

			currentPoint.first = round(getAlpha(t) * startX + getBeta(t) * endX + getGamma(t) * startDirection.first + getDelta(t) * endDirection.first);
			currentPoint.second = round(getAlpha(t) * startY + getBeta(t) * endY + getGamma(t) * startDirection.second + getDelta(t) * endDirection.second);

			if (*(this->pts->begin() + this->pts->size() - 1) != currentPoint) {
				this->pts->push_back(currentPoint);
			}
		}
	}
}