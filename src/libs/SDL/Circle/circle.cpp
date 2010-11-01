#include <cmath>
#include <iostream>
using namespace std;

#include "circle.hpp"
#include "../Pixel/pixel.hpp"

namespace sdl {

	inline float distance(Ui16 aX, Ui16 aY, Ui16 bX, Ui16 bY) {
		return sqrt((aX - bX) * (aX - bX) + (aY - bY) * (aY - bY));
	}

	void drawCircle(
			SDL_Surface *surface,
			Ui16 x,
			Ui16 y,
			Ui32 color,
			Ui16 radius
			) {
		if (radius == 0) {
			return;
		}

		//определяем границы квадрата вложенного в круг
		Ui16 squareHalfWidth = (Ui16) (radius * (M_SQRT2 / 2));
		Ui16 leftTopX, leftTopY;
		Ui16 rightDownX, rightDownY;

		//считаем координаты верхней левой и нижней правой точки
		if ((x - squareHalfWidth) > 0) {
			leftTopX = x - squareHalfWidth;
		} else {
			leftTopX = 0;
		}
		rightDownX = x + squareHalfWidth;
		if ((y - squareHalfWidth) > 0) {
			leftTopY = y - squareHalfWidth;
		} else {
			leftTopY = 0;
		}
		rightDownY = y + squareHalfWidth;

		Ui16 i, j;
		for (i = leftTopX; i <= rightDownX; i++) {
			for (j = leftTopY; j <= rightDownY; j++) {
				try {
					putpixel(surface, i, j, color);
				} catch (BadPixelException &ex) {
					cerr << ex.what() << endl;
				}
			}
		}

		//считаем 4 точки прямоугольников
		Ui16 aX, aY;
		Ui16 bX, bY;
		Ui16 cX, cY;
		Ui16 dX, dY;

		if ((x - radius) > 0) {
			aX = x - radius;
		} else {
			aX = 0;
		}
		aY = rightDownY;

		if ((y - radius) > 0) {
			bY = y - radius;
		} else {
			bY = 0;
		}
		bX = rightDownX;

		cX = x + radius;
		cY = leftTopY;

		dY = y + radius;
		dX = leftTopX;

		//рисуем каждый из четырех прямоугольников
		for (i = aX; i < leftTopX; i++) {
			for (j = leftTopY; j <= aY; j++) {
				if (distance(x, y, i, j) <= radius) {
					try {
						putpixel(surface, i, j, color);
					} catch (BadPixelException &ex) {
						cerr << ex.what() << endl;
					}
				}
			}
		}

		for (i = leftTopX; i < bX; i++) {
			for (j = bY; j <= leftTopY; j++) {
				if (distance(x, y, i, j) <= radius) {
					try {
						putpixel(surface, i, j, color);
					} catch (BadPixelException &ex) {
						cerr << ex.what() << endl;
					}
				}
			}
		}

		for (i = rightDownX; i < cX; i++) {
			for (j = cY; j <= rightDownY; j++) {
				if (distance(x, y, i, j) <= radius) {
					try {
						putpixel(surface, i, j, color);
					} catch (BadPixelException &ex) {
						cerr << ex.what() << endl;
					}
				}
			}
		}

		for (i = dX; i < rightDownX; i++) {
			for (j = rightDownY; j <= dY; j++) {
				if (distance(x, y, i, j) <= radius) {
					try {
						putpixel(surface, i, j, color);
					} catch (BadPixelException &ex) {
						cerr << ex.what() << endl;
					}
				}
			}
		}
	}
}