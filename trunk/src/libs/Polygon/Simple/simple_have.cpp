#include "simple.hpp"

namespace polygon {

	//проводим горизонтальную прямую

	bool Simple::have(const Point &p) const {
		Pi controlY = p.second;
		Pi controlX = p.first;

		Point prevPoint = *(this->pts->begin() + this->pts->size() - 1);
		Point currentPoint;

		vector<Point>::const_iterator it;
		bool result = false;
		for (it = this->pts->begin(); it != this->pts->end(); it++) {
			currentPoint = *it;

			if (controlX == currentPoint.first && controlY == currentPoint.second) {
				return true;
			}

			if((currentPoint.second <= controlY && controlY < prevPoint.second) || (prevPoint.second <= controlY && controlY < currentPoint.second)) {
				if(controlX > ((f32) prevPoint.first - currentPoint.first) * (controlY - currentPoint.second) / (prevPoint.second - currentPoint.second) + currentPoint.first) {
					result = !result;
				}
			}

			prevPoint = currentPoint;
		}

		return result;
	}
}