#include "convex.hpp"
#include <cmath>

namespace polygon {

	//правая или левая тройка из векторов (b, a), (b, c) и ((b, a) x (b, c))

	inline bool determinantSignum(const Point &a, const Point &b, const Point &c) {
		return (((a.first - b.first) * (c.second - b.second) - (c.first - b.first) * (a.second - b.second)) >= 0);
	}

	void Convex::jarvis(const vector<Point> &src) {

		vector<Point> srcCopy = src;

		//найдем самую нижнюю точку
		//если их несколько - выберем самую левую
		//такая политика обеспечит более удачную сложность в общем случае O(hn)
		vector<Point>::iterator it;
		vector<Point>::iterator leftDownIt = srcCopy.begin();
		Point currentPoint;
		Point leftDownPoint = *(leftDownIt);
		for (it = srcCopy.begin() + 1; it != srcCopy.end(); it++) {
			currentPoint = *it;
			if (currentPoint.first < leftDownPoint.first) {
				leftDownPoint = currentPoint;
				leftDownIt = it;
			} else if (currentPoint.first == leftDownPoint.first) {
				if (currentPoint.second > leftDownPoint.second) {
					leftDownPoint = currentPoint;
					leftDownIt = it;
				}
			}
		}
		//удалим эту точку и будем использовать ее как стартовую
		srcCopy.erase(leftDownIt);
		this->pts->push_back(leftDownPoint);

		//берем точку currentPoint и просматриваем относительно нее все точки
		currentPoint = leftDownPoint;

		Point nextPoint, tryPoint;
		vector<Point>::iterator nextIt;
		do {

			//если currentPoint == leftDownPoint то следующий фор сменит nextPoint
			//если фор не сменит leftDownPoint - полигон замкнулся - break
			if (determinantSignum(nextPoint, currentPoint, leftDownPoint)) {
				nextPoint = leftDownPoint;
				nextIt = it;
			}

			for (it = srcCopy.begin(); it != srcCopy.end(); it++) {
				tryPoint = *it;
				//если поворот вправо
				if (determinantSignum(nextPoint, currentPoint, tryPoint)) {
					nextPoint = tryPoint;
					nextIt = it;
				}
			}

			srcCopy.erase(nextIt);
			this->pts->push_back(nextPoint);
			currentPoint = nextPoint;
			
		} while(nextPoint != leftDownPoint);
	}
}