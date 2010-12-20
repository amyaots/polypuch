#include "general.hpp"

namespace polygon {

	//получаем октанную координату

	inline Ui8 octanCoordinate(Si16 x, Si16 y) {
		if (x > 0 && y >= 0) {
			if (x > y) {
				return 1;
			} else {
				return 2;
			}
		} else if (x <= 0 && y > 0) {
			if (-x < y) {
				return 3;
			} else {
				return 4;
			}
		} else if (x < 0 && y <= 0) {
			if (-x > -y) {
				return 5;
			} else {
				return 6;
			}
		} else {
			if (x < -y) {
				return 7;
			} else {
				return 8;
			}
		}
	}

	//определитель

	inline Si32 determinant(Si16 aX, Si16 aY, Si16 bX, Si16 bY) {
		return aX * bY - bX * aY;
	}

	//метод октанных координат

	bool General::have(const Point &p) const {

		Pi pX = p.first;
		Pi pY = p.second;

		Point prev = *(this->pts->begin() + this->pts->size() - 1);
		Point next;

		//итоговая сумма
		Si32 sum = 0;

		//разница октанных координат
		Si8 delta;

		//определитель
		Si32 det;

		//относительные координаты
		Si16 prevX = prev.first - pX;
		Si16 prevY = prev.second - pY;
		Si16 nextX, nextY;

		Ui8 octanPrev = octanCoordinate(prevX, prevY);
		Ui8 octanNext;

		vector<Point>::const_iterator it;
		for (it = this->pts->begin(); it != this->pts->end(); it++) {
			next = *it;

			nextX = next.first - pX;
			nextY = next.second - pY;

			octanNext = octanCoordinate(nextX, nextY);
			delta = octanNext - octanPrev;

			if (delta > 4) {
				delta -= 8;
			} else if (delta < -4) {
				delta += 8;
			} else if(delta == 4 || delta == -4) {
				det = determinant(prevX, prevY, nextX, nextY);
				if (det > 0) {
					delta = 4;
				} else if (det < 0) {
					delta = -4;
				} else {
					prev = next;

					prevX = nextX;
					prevY = nextY;

					octanPrev = octanNext;
					continue;
				}
			}

			sum += delta;

			prev = next;

			prevX = nextX;
			prevY = nextY;

			octanPrev = octanNext;
		}

		if (sum == 8 || sum == -8) {
			return true;
		} else {
			return false;
		}
	}
}