#include "convex.hpp"

#include <boost/unordered_map.hpp>
using namespace boost;

namespace polygon {

	typedef unordered_map<Point, f32> angleHash;

	inline void print(const Point &a) {
		cout << "(" << a.first << ", " << a.second << ")" << endl;
	}

	//получаем тангенс угла между вектором (from, to) и осью х
	f32 Convex::getAngle(Point from, Point to) {
		Si16 dX = to.first - from.first;
		if (dX) {
			return ((f32) to.second - from.second) / dX;
		} else {
			return f32_Max;
		}
	}

	//правая или левая тройка из векторов (b, a), (b, c) и ((b, a) x (b, c))
	bool Convex::determinantSignum(const Point &a, const Point &b, const Point &c) {
		return (((a.first - b.first) * (c.second - b.second) - (c.first - b.first) * (a.second - b.second)) >= 0);
	}

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

	void Convex::graham(const vector<Point> &src) {

		vector<Point> srcCopy = src;

		if (srcCopy.size() < 4) {
			*(this->pts) = srcCopy;
			return;
		}

		//выбираем одну из самых левых по иксу точек
		//тангенс угла между осью ох и вектором (стартовая точка, текущая точка) будет от -инф до + инф
		vector<Point>::iterator it;
		Pi smalestX = Pi_Max;
		Pi smalestY = Pi_Max;
		Point smalestPoint, current;
		vector<Point>::iterator smalestIt;
		for (it = srcCopy.begin(); it != srcCopy.end(); it++) {
			current = *it;
			if (smalestX > current.first) {
				smalestX = current.first;
				smalestY = current.second;
				smalestPoint = current;
				smalestIt = it;
			} else if(smalestX == current.first) {
				if (smalestY > current.second) {
					smalestX = current.first;
					smalestY = current.second;
					smalestPoint = current;
					smalestIt = it;
				}
			}
		}
		srcCopy.erase(smalestIt);

		angleHash angles;

		//посчитаем углы
		Point currentPoint;
		Si16 dX;
		for (it = srcCopy.begin(); it != srcCopy.end(); it++) {
			currentPoint = *it;
			angles[currentPoint] = getAngle(smalestPoint, currentPoint);
		}

		PolarAngleLess predicate(smalestPoint, angles);
		sort(srcCopy.begin(), srcCopy.end(), predicate);
		//от дубликаты точек могут быть гадкие баги
		//лучше мы их после сортировки все удалим за о(н)
		srcCopy.erase(unique(srcCopy.begin(), srcCopy.end()), srcCopy.end());

		//for_each(srcCopy.begin(), srcCopy.end(), print);
		//cout << endl;

		//добавляем стартовую и следующую за ней две точку
		//очевидно что это можно сделать (точки не могут сопасть друг с другом)

		this->pts->push_back(smalestPoint);
		this->pts->push_back(*(srcCopy.begin()));
		this->pts->push_back(*(srcCopy.begin() + 1));

		Point nextPoint;
		Point prevPoint;
		vector<Point>::iterator jt;
		for (it = srcCopy.begin() + 2; it != srcCopy.end(); it++) {
			currentPoint = *it;

			this->pts->push_back(currentPoint);

			//for_each(this->pts->begin(), this->pts->end(), print);
			//cout << endl;

			//проходим по точкам назад пока не встретим нормальную ситуацию
			prevPoint = currentPoint;
			for (jt = this->pts->begin() + this->pts->size() - 2; jt != this->pts->begin(); jt--) {
				currentPoint = *jt;
				nextPoint = *(jt - 1);

				//print(nextPoint);
				//print(currentPoint);
				//print(prevPoint);

				if (determinantSignum(nextPoint, currentPoint, prevPoint)) {
					this->pts->erase(jt);
					//cout << "deleted" << endl << endl;
				} else {
					//cout << endl;
					break;
				}
			}
		}
	}
}