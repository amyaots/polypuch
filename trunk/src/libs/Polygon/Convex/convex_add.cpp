#include "convex.hpp"

#include "../../Segments/Common/common.hpp"
using namespace segments;

namespace polygon {

	//правая или левая тройка из векторов (b, a), (b, c) и ((b, a) x (b, c))

	inline bool determinantSignum(const Point &a, const Point &b, const Point &c) {
		return (((a.first - b.first) * (c.second - b.second) - (c.first - b.first) * (a.second - b.second)) >= 0);
	}

	bool Convex::add(const Point &p) {

		Ui32 size = this->pts->size();
		//работаем только начиная с треугольника
		if (size < 2) {
			this->pts->push_back(p);
			return true;
		} else if (size == 2) {
			//добавляем так чтобы соблюдать обход по часовой стрелке
			if (determinantSignum(*(this->pts->begin()), *(this->pts->begin() + 1), p)) {
				this->pts->insert(this->pts->begin() + 1, p);
			} else {
				this->pts->push_back(p);
			}
			return true;
		}

		Point startPoint, endPoint;

		bool returnValue = false;

		vector<Point>::iterator it, jt;
		startPoint = *(this->pts->begin() + size - 1);
		bool erasing = false;
		bool added = false;

		//cout << "start" << endl;
		for (it = this->pts->begin(); it != this->pts->end(); it++) {
			endPoint = *it;

			//cout << "analyzing " << startPoint.first << ", " << startPoint.second << endl;
			//cout << "analyzing " << endPoint.first << ", " << endPoint.second << endl;

			if (determinantSignum(startPoint, endPoint, p)) {
				it = this->pts->erase(it) - 1;
				//cout << "deleting " << endPoint.first << ", " << endPoint.second << endl;
				erasing = true;
			} else {
				if (erasing) {
					it = this->pts->insert(it, p);
					it++;
					it = this->pts->insert(it, startPoint);
					it++;
					//cout << "adding " << startPoint.first << ", " << startPoint.second << endl;
					added = true;
					returnValue = true;
					erasing = false;
				}
			}
			//cout << endl;
			//for (jt = this->pts->begin(); jt != this->pts->end(); jt++) {
			//	cout << "" << (*jt).first << ", " << (*jt).second << endl;
			//}
			//cout << endl;

			startPoint = endPoint;
		}
		if (erasing && !added) {
			it = this->pts->insert(it, p);
			it++;
			it = this->pts->insert(it, startPoint);
			//cout << "adding " << startPoint.first << ", " << startPoint.second << endl;
			//cout << endl;
			returnValue = true;
		}
		//cout << "end" << endl << endl;

		//cout << "start" << endl;
		//for (jt = this->pts->begin(); jt != this->pts->end(); jt++) {
		//	cout << "" << (*jt).first << ", " << (*jt).second << endl;
		//}
		//cout << "end" << endl << endl;

		return returnValue;

		/*
		Ui32 size = this->pts->size();
		//работаем только начиная с треугольника
		if (size < 3) {
			this->pts->push_back(p);
			return true;
		}

		Point leftPoint, rightPoint;

		//возьмем 3 точки которые по-любому есть
		Point firstPoint = *(this->pts->begin());
		Point secondPoint = *(this->pts->begin() + 1);
		Point thirdPoint = *(this->pts->begin() + 2);

		//возьмем 2 точки на середине двух отрезков
		Point firstSecondPoint = Point((firstPoint.first + secondPoint.first) / 2, (firstPoint.second + secondPoint.second) / 2);
		Point secondThirdPoint = Point((firstPoint.first + thirdPoint.first) / 2, (firstPoint.second + thirdPoint.second) / 2);

		//пересечем 2 медианы и получим точку внутри полигона
		Point insidePoint;
		segmentsIntersect(thirdPoint, firstSecondPoint, firstPoint, secondThirdPoint, insidePoint);

		Ui16 startPos, endPos, currentPos;
		startPos = 0;
		endPos = size;

		Point startPoint, endPoint, currentPoint;
		startPoint = *(this->pts->begin());
		endPoint = startPoint;

		//определим в каком векторе находится точка p
		while (endPos - startPos > 1) {
			currentPos = startPos + floor(((f32) endPos - startPos) / 2);
			currentPoint = this->pts->operator [](currentPos);

			if (!determinantSignum(startPoint, insidePoint, p) || !determinantSignum(p, insidePoint, currentPoint)) {
				//не в секторе (start, inside, current)
				startPoint = currentPoint;
				startPos = currentPos;
				continue;
			}

			//в секторе (start, inside, current)
			endPoint = currentPoint;
			endPos = currentPos;
		}
		Ui16 oldStartPos, oldEndPos;
		oldStartPos = startPos;
		oldEndPos = endPos;
		//точка p в секторе (start, end)
		//точки start и end находяться в секторе прикрепления

		//cout << startPoint.first << ", " << startPoint.second << endl;
		//cout << endPoint.first << ", " << endPoint.second << endl << endl;

		//определим крайнюю левую точку прикрепления (смотря из точки p на полигон)
		Point nextPoint;
		endPos = ((Ui16) (endPos + floor(((f32) size - endPos + startPos) / 2))) % size;
		while (size - endPos + startPos > 1) {
			currentPos = ((Ui16) (endPos + floor(((f32) size - endPos + startPos) / 2))) % size;
			currentPoint = this->pts->operator [](currentPos);
			nextPoint = this->pts->operator []((currentPos + 1) % size);

			if (!determinantSignumComplex(currentPoint, insidePoint, nextPoint, currentPoint)) {
				//не в секторе (start, inside, current)
				startPoint = currentPoint;
				startPos = currentPos;
				continue;
			}

			//в секторе (start, inside, current)
			endPoint = currentPoint;
			endPos = currentPos;
		}

		//определим крайнюю правую точку прикрепления (смотря из точки p на полигон)
		startPos = oldStartPos;
		endPos = oldEndPos;

		startPos = ((Ui16) (endPos + floor(((f32) size - endPos + startPos) / 2))) % size;
		while (size - endPos + startPos > 1) {
			currentPos = ((Ui16) (endPos + floor(((f32) size - endPos + startPos) / 2))) % size;
			currentPoint = this->pts->operator [](currentPos);
			nextPoint = this->pts->operator []((currentPos + 1) % size);

			if (determinantSignumComplex(currentPoint, insidePoint, nextPoint, currentPoint)) {
				//не в секторе (start, inside, current)
				startPoint = currentPoint;
				startPos = currentPos;
				continue;
			}

			//в секторе (start, inside, current)
			endPoint = currentPoint;
			endPos = currentPos;
		}

		return true;
		 * */
	}
}