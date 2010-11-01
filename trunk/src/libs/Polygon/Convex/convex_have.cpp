#include "convex.hpp"
#include "cmath"

namespace polygon {

	//правая или левая тройка из векторов (b, a), (b, c) и ((b, a) x (b, c))
	bool Convex::determinantSignum(const Point &a, const Point &b, const Point &c) {
		return (((a.first - b.first) * (c.second - b.second) - (c.first - b.first) * (a.second - b.second)) >= 0);
	}

	//реализуем без нахождения центральной точки

	bool Convex::have(const Point &p) const {
		Ui32 size = this->pts->size();
		if (size == 0) {
			//никаких точек нет
			//так дело не пойдет
			return false;
		}
		if (size == 1) {
			//если всего одна точка - проверим на совпадение
			Point firstPoint = *(this->pts->begin());
			return (firstPoint.first == p.first && firstPoint.second == p.second);
		}
		
		if (size == 2) {
			//подставим в уравнение прямой
			//y = Mx + N
			
			f32 M, N;
			Point firstPoint = *(this->pts->begin());
			Point secondPoint = *(this->pts->begin() + 1);

			f32 Z1 = secondPoint.first - firstPoint.first;
			if (Z1) {
				M = ((f32) secondPoint.second - firstPoint.second) / Z1;
				N = ((f32) firstPoint.second * secondPoint.first - firstPoint.first * secondPoint.second) / Z1;
				return (p.second == ceil(M * p.first + N) && (firstPoint.first - p.first) * (secondPoint.first - p.first) <= 0 && (firstPoint.second - p.second) * (secondPoint.second - p.second) <= 0);
			} else {
				return (p.first == firstPoint.first && (firstPoint.second - p.second) * (secondPoint.second - p.second) <= 0);
			}
		}

		Point firstPoint = *(this->pts->begin());

		Ui16 startPos, endPos, currentPos;
		startPos = 1;
		endPos = size - 1;

		Point startPoint, endPoint, currentPoint;
		startPoint = *(this->pts->begin() + 1);
		endPoint = *(this->pts->begin() + size - 1);

		if (!determinantSignum(startPoint, firstPoint, p) || !determinantSignum(p, firstPoint, endPoint)) {
			return false;
		}
		//вот теперь отталкиваемся от первой точки как от центральной

		while (endPos - startPos > 1) {
			currentPos = startPos + floor(((f32) endPos - startPos) / 2);
			currentPoint = this->pts->operator [](currentPos);
			
			if (!determinantSignum(startPoint, firstPoint, p) || !determinantSignum(p, firstPoint, currentPoint)) {
				//не в секторе (start, first, current)
				startPoint = currentPoint;
				startPos = currentPos;
				continue;
			}

			//в секторе (start, first, current)
			endPoint = currentPoint;
			endPos = currentPos;
		}
		//треугольник (start, first, end) выловлен

		//мы знаем что (first, start) имеет меньший тангенс наклона относительно оси х, чем (first, end)
		//вывод: тройка из векторов (start, first), (start, end) и ((start, first) x (start, end)) правая
		//значит точка лежит вне треугольника, если тройка из векторов (start, end), (start, p) и ((start, end) x (start, p)) тоже правая

		return (determinantSignum(endPoint, startPoint, p));
	}
}