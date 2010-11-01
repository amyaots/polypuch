#include <SDL.h>
#include <cmath>
#include "line.hpp"
#include "../Pixel/pixel.hpp"
#include <iostream>
using namespace std;

namespace sdl {

	void drawLine(
			SDL_Surface *surface,
			Uint16 aX,
			Uint16 aY,
			Uint16 bX,
			Uint16 bY,
			Uint32 color,
			Uint16 width
			) {
		if (width == 0) {
			return;
		}

		//толщина линии сверху от основной линии и под ней
		Uint16 widthUpWidth = (Uint16) floor((float) (width - 1) / 2);
		Uint16 widthDownWidth = width - 1 - widthUpWidth;

		//угол наклона линии по отношению к оси Х
		float length = sqrt((float) (bX - aX) * (bX - aX) + (bY - aY) * (bY - aY));
		if (!length) {
			return;
		}
		float cosBeta = (float) (bX - aX) / length;
		float sinBeta = (float) (bY - aY) / length;

		//основной алгоритм требует чтобы косинус бета был отличен от нуля
		if (cosBeta == 0) {
			Uint16 x, y;
			Uint16 topY, downY;
			if (aY <= bY) {
				topY = bY;
				downY = aY;
			} else {
				topY = aY;
				downY = bY;
			}
			Uint16 rightX = aX + widthUpWidth;
			for (x = aX - widthDownWidth; x <= rightX; x++) {
				for (y = downY; y <= topY; y++) {
					try {
						putpixel(surface, x, y, color);
					} catch (BadPixelException &ex) {
						cerr << ex.what() << endl;
					}
				}
			}

			return;
		}

		//основной алгоритм требует чтобы cинус бета был отличен от нуля
		if (sinBeta == 0) {
			Uint16 x, y;
			Uint16 leftX, rightX;
			if (aX <= bX) {
				leftX = aX;
				rightX = bX;
			} else {
				leftX = bX;
				rightX = aX;
			}
			Uint16 rightY = aY + widthUpWidth;
			for (x = leftX; x <= rightX; x++) {
				for (y = aY - widthDownWidth; y <= rightY; y++) {
					try {
						putpixel(surface, x, y, color);
					} catch (BadPixelException &ex) {
						cerr << ex.what() << endl;
					}
				}
			}

			return;
		}

		Uint16 horizontalSize = abs(bX - aX);
		Uint16 verticalSize = abs(bY - aY);

		//вычисляем отступ стартовой точки
		//выбираем напрявляющий вектор единичной длины перпендикуляра - (-sinBeta, cosBeta)
		Sint16 startToLeft = (Sint16) ceil(widthUpWidth * -sinBeta);
		Sint16 startToRight = (Sint16) ceil(widthUpWidth * cosBeta);
		if ((aX + startToLeft) >= 0) {
			aX += startToLeft;
		} else {
			aX = 0;
		}
		if ((bX + startToLeft) >= 0) {
			bX += startToLeft;
		} else {
			bX = 0;
		}
		if ((aY + startToRight) >= 0) {
			aY += startToRight;
		} else {
			aY = 0;
		}
		if ((bY + startToRight) >= 0) {
			bY += startToRight;
		} else {
			bY = 0;
		}

		//знак в какую сторону двигаться по осям. от точки А до точки Б
		Sint8 xSignum, ySignum;
		if (bX >= aX) {
			xSignum = 1;
		} else {
			xSignum = -1;
		}
		if (bY >= aY) {
			ySignum = 1;
		} else {
			ySignum = -1;
		}

		//знак в какую сторону двигаться по перпендикуляру.
		//т.к. напрявляющий вектор единичной длины перпендикуляра - (-sinBeta, cosBeta)
		//то движемся в противоположную сторону - (sinBeta, -cosBeta)
		Sint8 xOrtSignum, yOrtSignum;
		if (sinBeta > 0) {
			xOrtSignum = 1;
		} else {
			xOrtSignum = -1;
		}
		if (cosBeta < 0) {
			yOrtSignum = 1;
		} else {
			yOrtSignum = -1;
		}

		Uint8 blockSize;
		Sint16 x, y, xi, yi;

		if (horizontalSize >= verticalSize) {

			//поменяем точки местами если Б перед А по оси х.
			if (bX < aX) {
				ySignum *= -1;
				xSignum *= -1;

				Uint16 temp;

				temp = aX;
				aX = bX;
				bX = temp;

				temp = aY;
				aY = bY;
				bY = temp;
			}

			//движемся по оси х вправо по блокам
			//движемся по оси у в зависимости от знака

			blockSize = (Uint8) ceil((float) horizontalSize / verticalSize);

			//смещаемся по щирине в направлении (sinBeta, -cosBeta)
			//по блокам увеличиваем y на yOrtSignum, x на xOrtSignum

			//если передвигаем блок, то необходимо заткнуть еще один "мертвый" пиксель
			//поворот прямоугольника неинъективен на мн-ве пикселей
			bool addPixel = false;

			if (xOrtSignum == -1) {
				//смещение по х влево.
				//"мертвый" пиксель затыкается в первом ряду

				for (yi = 0; yi < width; yi++) {
					if (yi % blockSize == 0 && yi) {
						aX += xOrtSignum;
						bX += xOrtSignum;
						addPixel = true;
					} else {
						addPixel = false;
					}

					for (x = aX, y = aY; x <= bX; x++) {
						if (x != aX && (x - aX) % blockSize == 0) {
							//мы находимся над началом нового блока
							//затыкаем пиксель

							if (addPixel) {
								try {
									putpixel(surface, x, y, color);
								} catch (BadPixelException &ex) {
									cerr << ex.what() << endl;
								}
							}

							y += ySignum;
						}

						try {
							putpixel(surface, x, y, color);
						} catch (BadPixelException &ex) {
							cerr << ex.what() << endl;
						}
					}

					aY += yOrtSignum;
					bY += yOrtSignum;
				}
			} else {
				//смещение по х влево.
				//"мертвый" пиксель затыкается в последнем ряду ряду

				for (yi = 0; yi < width; yi++) {
					if (yi % blockSize == 0 && yi) {
						aX += xOrtSignum;
						bX += xOrtSignum;
					}

					if (yi != (width - 1) && yi % blockSize == blockSize - 1) {
						addPixel = true;
					} else {
						addPixel = false;
					}

					for (x = aX, y = aY; x <= bX; x++) {
						if (x != aX && (x - aX) % blockSize == 0) {
							//мы находимся над началом нового блока
							//затыкаем пиксель

							if (addPixel) {
								try {
									putpixel(surface, x, y, color);
								} catch (BadPixelException &ex) {
									cerr << ex.what() << endl;
								}
							}

							y += ySignum;
						}

						try {
							putpixel(surface, x, y, color);
						} catch (BadPixelException &ex) {
							cerr << ex.what() << endl;
						}
					}

					aY += yOrtSignum;
					bY += yOrtSignum;
				}
			}
		} else {

			//поменяем точки местами если Б перед А по оси y.
			if (bY < aY) {
				ySignum *= -1;
				xSignum *= -1;

				Uint16 temp;

				temp = aX;
				aX = bX;
				bX = temp;

				temp = aY;
				aY = bY;
				bY = temp;
			}

			//движемся по оси у вверх по блокам
			//движемся по оси х в зависимости от знака

			blockSize = (Uint8) ceil((float) verticalSize / horizontalSize);

			//смещаемся по щирине в направлении (sinBeta, -cosBeta)
			//по блокам увеличиваем y на yOrtSignum, x на xOrtSignum

			//если передвигаем блок, то необходимо заткнуть еще один "мертвый" пиксель
			//поворот прямоугольника неинъективен на мн-ве пикселей
			bool addPixel = false;

			if (yOrtSignum == -1) {
				//смещение по y вверх.
				//"мертвый" пиксель затыкается в первом ряду

				for (xi = 0; xi < width; xi++) {
					if (xi % blockSize == 0 && xi) {
						aY += yOrtSignum;
						bY += yOrtSignum;
						addPixel = true;
					} else {
						addPixel = false;
					}

					for (y = aY, x = aX; y <= bY; y++) {
						if (y != aY && (y - aY) % blockSize == 0) {
							//мы находимся над началом нового блока
							//затыкаем пиксель

							if (addPixel) {
								try {
									putpixel(surface, x, y, color);
								} catch (BadPixelException &ex) {
									cerr << ex.what() << endl;
								}
							}

							x += xSignum;
						}

						try {
							putpixel(surface, x, y, color);
						} catch (BadPixelException &ex) {
							cerr << ex.what() << endl;
						}
					}

					aX += xOrtSignum;
					bX += xOrtSignum;
				}
			} else {
				//смещение по y вниз.
				//"мертвый" пиксель затыкается в последнем ряду ряду

				for (xi = 0; xi < width; xi++) {
					if (xi % blockSize == 0 && xi) {
						aY += yOrtSignum;
						bY += yOrtSignum;
					}

					if (xi != (width - 1) && xi % blockSize == blockSize - 1) {
						addPixel = true;
					} else {
						addPixel = false;
					}

					for (y = aY, x = aX; y <= bY; y++) {
						if (y != aY && (y - aY) % blockSize == 0) {
							//мы находимся над началом нового блока
							//затыкаем пиксель

							if (addPixel) {
								try {
									putpixel(surface, x, y, color);
								} catch (BadPixelException &ex) {
									cerr << ex.what() << endl;
								}
							}

							x += xSignum;
						}

						try {
							putpixel(surface, x, y, color);
						} catch (BadPixelException &ex) {
							cerr << ex.what() << endl;
						}
					}

					aX += xOrtSignum;
					bX += xOrtSignum;
				}
			}
		}
	}

}