#include "bezier.hpp"

#include <cmath>
#include <list>
#include <algorithm>

#include "../../SDL/Pixel/pixel.hpp"
using namespace sdl;

namespace curve {

	//кривая Безье

	void Bezier::approximate(const vector<Point> &controlPoints) {

		this->controlPoints = controlPoints;

		size_t size = controlPoints.size();

		if (size < 3) {
			cerr << "controlPoints.size() < 3 !" << endl;
			return;
		}

		Point startPoint, endPoint, currentPoint;

		Pi maxLength = 0;

		vector<Point>::const_iterator cit;
		startPoint = *(controlPoints.begin());
		for (cit = controlPoints.begin() + 1; cit != controlPoints.end(); cit++) {
			endPoint = *cit;

			maxLength += ceil(sqrt((endPoint.first - startPoint.first) * (endPoint.first - startPoint.first) + (endPoint.second - startPoint.second) * (endPoint.second - startPoint.second)));

			startPoint = endPoint;
		}

		f32 t;
		f32 step = 1.0 / maxLength;

		pair<f32, f32> startPointF, endPointF, currentPointF;
		list<pair<f32, f32> >::iterator it;
		list<pair<f32, f32> > points;

		//пересоздадим множество точек по параметру t
		this->pts->clear();

		for (t = 0; t <= 1; t += step) {

			copy(controlPoints.begin(), controlPoints.end(), back_inserter(points));

			while (points.size() > 1) {

				startPointF = *(points.begin());
				points.pop_front();
				for (it = points.begin(); it != points.end(); it++) {
					endPointF = *it;

					it->first = startPointF.first + (endPointF.first - startPointF.first) * t;
					it->second = startPointF.second + (endPointF.second - startPointF.second) * t;

					startPointF = endPointF;
				}
			}

			currentPointF = points.front();
			points.pop_front();

			currentPoint.first = round(currentPointF.first);
			currentPoint.second = round(currentPointF.second);

			this->pts->push_back(currentPoint);
		}
	}

	Point Bezier::getPoint(f32 t) const {
		while (t > 1) {
			t -= 1;
		}
		size_t lastIndex = this->pts->size() - 1;
		return this->pts->at(lastIndex * t);
	}
}