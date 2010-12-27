#include "convex.hpp"
#include <cmath>

#include <boost/unordered_map.hpp>
using namespace boost;

namespace polygon {

	//правая или левая тройка из векторов (b, a), (b, c) и ((b, a) x (b, c))

	inline bool determinantSignum(const Point &a, const Point &b, const Point &c) {
		return (((a.first - b.first) * (c.second - b.second) - (c.first - b.first) * (a.second - b.second)) >= 0);
	}

	//модуль векторного произведения |(currentPoint, a) x (currentPoint, a)|

	inline f32 square(const Point &a, const Point &currentPoint, const Point &b) {
		return sqrt(abs(((f32) a.first - currentPoint.first) * ((f32) b.second - currentPoint.second) - ((f32) a.second - currentPoint.second) * ((f32) b.first - currentPoint.first)));
	}

	typedef unordered_map<Point, f32> angleHash;

	//предикат сравнения точек по угловому приницпу

	class PolarAngleLess {
	private:
		angleHash angles;
		Point start;

	public:

		PolarAngleLess(const Point &start, const angleHash &angles) {
			this->start = start;
			this->angles = angles;
		}

		//a наблюжается из точки старт под меньшим углом чем б

		bool operator()(const Point &a, const Point &b) {
			return (this->angles[a]) < (this->angles[b]);
		}
	};

	inline f32 getAngle(Point from, Point to) {
		Si16 dX = to.first - from.first;
		if (dX) {
			return ((f32) to.second - from.second) / dX;
		} else {
			return f32_Max;
		}
	}

	void hoare_recursive(const Point &a, const Point &b, vector<Point> &src, vector<Point> *result) {
		Point currentPoint, maxPoint;
		f32 maxSquare = 0, currentSquare;

		//найдем точку такую что треугольник a, b, maxPoint имеет максимальную площадь
		vector<Point>::iterator it, maxIt;
		for (it = src.begin(); it != src.end(); it++) {
			currentPoint = *it;
			currentSquare = square(a, currentPoint, b);
			if (currentSquare > maxSquare) {
				maxSquare = currentSquare;
				maxPoint = currentPoint;
				maxIt = it;
			}
		}

		//удалим maxIt из сорса и добавим в результат
		maxIt = src.erase(maxIt);
		result->push_back(maxPoint);

		cout << "maxPoint" << endl;
		cout << maxPoint.first << ", " << maxPoint.second << endl;
		cout << endl;

		vector<Point> src1, src2;

		bool aMaxRotate, bMaxRotate, aBRotate;

		cout << "erase points" << endl;
		for (it = src.begin(); it != src.end(); it++) {
			currentPoint = *it;
			aBRotate = determinantSignum(a, currentPoint, b);
			bMaxRotate = determinantSignum(b, currentPoint, maxPoint);
			aMaxRotate = determinantSignum(maxPoint, currentPoint, a);

			cout << "aMaxRotate " << aMaxRotate << endl;
			cout << "bMaxRotate " << bMaxRotate << endl;
			cout << "aBRotate " << aBRotate << endl;

			if (
					(aMaxRotate && bMaxRotate && aBRotate) ||
					(!aMaxRotate && !bMaxRotate && !aBRotate)
					) {
				//удалим все точки лежащие в треугольнике
				cout << currentPoint.first << ", " << currentPoint.second << endl;
				it = src.erase(it) - 1;
			} else if (
					(!aMaxRotate && bMaxRotate && aBRotate) ||
					(aMaxRotate && !bMaxRotate && !aBRotate)
					) {
				src1.push_back(currentPoint);
			} else {
				src2.push_back(currentPoint);
			}
		}
		cout << endl;

		if (src1.size() > 0) {
			cout << "first" << endl << endl;
			for (it = src1.begin(); it != src1.end(); it++) {
				cout << (*it).first << ", " << (*it).second << endl;
			}
			cout << endl;

			hoare_recursive(a, maxPoint, src1, result);
		} else {
			cout << "first clear" << endl << endl;
		}

		if (src2.size() > 0) {
			cout << "second" << endl << endl;
			for (it = src2.begin(); it != src2.end(); it++) {
				cout << (*it).first << ", " << (*it).second << endl;
			}
			cout << endl;

			hoare_recursive(b, maxPoint, src2, result);
		} else {
			cout << "second clear" << endl << endl;
		}
	}

	void Convex::hoare(const vector<Point> &src) {
		if (src.size() < 4) {
			vector<Point>::const_iterator it;
			for (it = src.begin(); it != src.end(); it++) {
				this->pts->push_back(*it);
			}
			return;
		}

		vector<Point> srcCopy = src;

		Point currentPoint, a, b;

		a.first = Pi_Max;
		a.second = Pi_Max;

		vector<Point>::iterator it, aIt, bIt;

		for (it = srcCopy.begin(); it != srcCopy.end(); it++) {
			currentPoint = *it;

			if (currentPoint.first < a.first) {
				a = currentPoint;
				aIt = it;
			} else if (currentPoint.first == a.first) {
				if (currentPoint.second < a.second) {
					a = currentPoint;
					aIt = it;
				}
			}
		}

		this->pts->push_back(a);
		srcCopy.erase(aIt);

		b.first = Pi_Min;
		b.second = Pi_Min;

		for (it = srcCopy.begin(); it != srcCopy.end(); it++) {
			currentPoint = *it;

			if (currentPoint.first > b.first) {
				b = currentPoint;
				bIt = it;
			} else if (currentPoint.first == b.first) {
				if (currentPoint.second > b.second) {
					b = currentPoint;
					bIt = it;
				}
			}
		}

		this->pts->push_back(b);
		srcCopy.erase(bIt);

		cout << a.first << ", " << a.second << endl;
		cout << b.first << ", " << b.second << endl;
		cout << endl;

		vector<Point> src1, src2;

		for (it = srcCopy.begin(); it != srcCopy.end(); it++) {
			currentPoint = *it;
			if (determinantSignum(a, b, currentPoint)) {
				src1.push_back(currentPoint);
			} else {
				src2.push_back(currentPoint);
			}
		}

		if (src1.size() > 0) {
			cout << "first" << endl << endl;
			for (it = src1.begin(); it != src1.end(); it++) {
				cout << (*it).first << ", " << (*it).second << endl;
			}
			cout << endl;

			hoare_recursive(a, b, src1, this->pts);
		} else {
			cout << "first clear" << endl;
		}

		if (src2.size() > 0) {
			cout << "second" << endl << endl;
			for (it = src2.begin(); it != src2.end(); it++) {
				cout << (*it).first << ", " << (*it).second << endl;
			}
			cout << endl;

			hoare_recursive(a, b, src2, this->pts);
		} else {
			cout << "second clear" << endl;
		}

		angleHash angles;

		//посчитаем углы
		Point startPoint = *(this->pts->begin());
		angles[startPoint] = -f32_Max;
		for (it = this->pts->begin() + 1; it != this->pts->end(); it++) {
			currentPoint = *it;
			angles[currentPoint] = getAngle(startPoint, currentPoint);
		}

		angleHash::iterator ait;

		for (ait = angles.begin(); ait != angles.end(); ait++) {
			cout << "[" << (*ait).first.first << ", " << (*ait).first.second << "] = " << ait->second << endl;
			;
		}
		cout << endl;

		PolarAngleLess predicate(startPoint, angles);
		sort(this->pts->begin(), this->pts->end(), predicate);

		for (ait = angles.begin(); ait != angles.end(); ait++) {
			cout << "[" << (*ait).first.first << ", " << (*ait).first.second << "] = " << ait->second << endl;
			;
		}
		cout << endl;
	}
}