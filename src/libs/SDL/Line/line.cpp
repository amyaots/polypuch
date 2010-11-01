#include <cmath>
#include <iostream>
#include <list>
using namespace std;

#include "line.hpp"
#include "../Pixel/pixel.hpp"
namespace sdl {

	void drawLine(
			SDL_Surface *surface,
			Ui16 aX,
			Ui16 aY,
			Ui16 bX,
			Ui16 bY,
			Ui32 color,
			Ui16 width
			) {
		if (width == 0) {
			return;
		}

		//толщина линии сверху от основной линии и под ней
		Ui16 widthUpWidth = (Ui16) floor((float) (width - 1) / 2);
		Ui16 widthDownWidth = width - 1 - widthUpWidth;

		//угол наклона линии по отношению к оси Х
		float length = sqrt((float) (bX - aX) * (bX - aX) + (bY - aY) * (bY - aY));
		if (!length) {
			return;
		}
		float cosBeta = (float) (bX - aX) / length;
		float sinBeta = (float) (bY - aY) / length;

		//основной алгоритм требует чтобы косинус бета был отличен от нуля
		if (cosBeta == 0) {
			Ui16 x, y;
			Ui16 topY, downY;
			if (aY <= bY) {
				topY = bY;
				downY = aY;
			} else {
				topY = aY;
				downY = bY;
			}
			Ui16 rightX = aX + widthUpWidth;
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
			Ui16 x, y;
			Ui16 leftX, rightX;
			if (aX <= bX) {
				leftX = aX;
				rightX = bX;
			} else {
				leftX = bX;
				rightX = aX;
			}
			Ui16 rightY = aY + widthUpWidth;
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

		Ui16 horizontalSize = abs(bX - aX);
		Ui16 verticalSize = abs(bY - aY);

		Ui16 horizontalWidth = floor(abs(sinBeta * width)) + 1;
		Ui16 verticalWidth = floor(abs(cosBeta * width)) + 1;

		//вычисляем отступ стартовой точки
		//выбираем напрявляющий вектор единичной длины перпендикуляра - (-sinBeta, cosBeta)
		Si16 startToLeft = (Si16) ceil(widthUpWidth * -sinBeta);
		Si16 startToRight = (Si16) ceil(widthUpWidth * cosBeta);
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
		Si8 xSignum, ySignum;
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
		//то движемся в одну из противоположных сторон - (sinBeta, -cosBeta)
		Si8 xOrtSignum, yOrtSignum;
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

		Ui16 blockSize;
		Si16 x, y, xi, yi;
		list<Ui16> blockSizes;
		list<Ui16>::iterator blockSizeI, blockSizeJ;
		Ui16 blockSizeICounter, blockSizeJCounter;

		if (horizontalSize >= verticalSize) {

			//поменяем точки местами если Б перед А по оси х.
			if (bX < aX) {
				ySignum *= -1;
				xSignum *= -1;

				Ui16 temp;

				temp = aX;
				aX = bX;
				bX = temp;

				temp = aY;
				aY = bY;
				bY = temp;
			}

			//движемся по оси х вправо по блокам
			//движемся по оси у в зависимости от знака

			//определяем последовательность размеров блоков
			//очевидно что стек блоков по оси х такой же как и по оси у
			Ui16 prevX = 0;
			float currentX = 0;
			float ctgBeta = abs(cosBeta / sinBeta);
			Ui16 j;
			for (j = 0; j < verticalSize; j++) {
				currentX += ctgBeta;
				blockSize = (Ui16) currentX - prevX;
				prevX += blockSize;
				blockSizes.push_back(blockSize);
			}

			blockSizeJ = blockSizes.begin();

			//смещаемся по щирине в направлении (sinBeta, -cosBeta)
			//по блокам увеличиваем y на yOrtSignum, x на xOrtSignum

			//если передвигаем блок, то необходимо заткнуть еще один "мертвый" пиксель
			//поворот прямоугольника неинъективен на мн-ве пикселей
			bool addPixel = false;

			if (xOrtSignum == -1) {

				//смещение по х влево.
				//"мертвый" пиксель затыкается в первом ряду

				blockSizeJCounter = *(blockSizeJ);

				for (yi = 0; yi < verticalWidth; yi++) {

					if (!blockSizeJCounter) {
						aX += xOrtSignum;
						bX += xOrtSignum;
						addPixel = true;
						blockSizeJ++;
						blockSizeJCounter = *(blockSizeJ);
					} else {
						addPixel = false;
					}

					blockSizeI = blockSizes.begin();
					blockSizeICounter = *(blockSizeI);

					for (x = aX, y = aY; x <= bX; x++) {

						if (!blockSizeICounter) {
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
							blockSizeI++;
							blockSizeICounter = *(blockSizeI);
						}

						try {
							putpixel(surface, x, y, color);
						} catch (BadPixelException &ex) {
							cerr << ex.what() << endl;
						}

						blockSizeICounter--;
					}

					aY += yOrtSignum;
					bY += yOrtSignum;
					blockSizeJCounter--;
				}
			} else {
				//смещение по х влево.
				//"мертвый" пиксель затыкается в последнем ряду

				blockSizeJCounter = *(blockSizeJ);

				for (yi = 0; yi < verticalWidth; yi++) {

					if (!blockSizeJCounter) {
						aX += xOrtSignum;
						bX += xOrtSignum;
						blockSizeJ++;
						blockSizeJCounter = *(blockSizeJ);
					}

					if (yi != (verticalWidth - 1) && blockSizeJCounter == 1) {
						addPixel = true;
					} else {
						addPixel = false;
					}

					blockSizeI = blockSizes.begin();
					blockSizeICounter = *(blockSizeI);

					for (x = aX, y = aY; x <= bX; x++) {

						if (!blockSizeICounter) {
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
							blockSizeI++;
							blockSizeICounter = *(blockSizeI);
						}

						try {
							putpixel(surface, x, y, color);
						} catch (BadPixelException &ex) {
							cerr << ex.what() << endl;
						}

						blockSizeICounter--;
					}

					aY += yOrtSignum;
					bY += yOrtSignum;
					blockSizeJCounter--;
				}
			}
		} else {

			//поменяем точки местами если Б перед А по оси y.
			if (bY < aY) {
				ySignum *= -1;
				xSignum *= -1;

				Ui16 temp;

				temp = aX;
				aX = bX;
				bX = temp;

				temp = aY;
				aY = bY;
				bY = temp;
			}

			//движемся по оси у вверх по блокам
			//движемся по оси х в зависимости от знака

			//определяем последовательность размеров блоков
			//очевидно что стек блоков по оси х такой же как и по оси у
			Ui16 prevY = 0;
			float currentY = 0;
			float tgBeta = abs(sinBeta / cosBeta);
			Ui16 i;
			for (i = 0; i < horizontalSize; i++) {
				currentY += tgBeta;
				blockSize = (Ui16) currentY - prevY;
				prevY += blockSize;
				blockSizes.push_back(blockSize);
			}

			blockSizeI = blockSizes.begin();

			//смещаемся по щирине в направлении (sinBeta, -cosBeta)
			//по блокам увеличиваем y на yOrtSignum, x на xOrtSignum

			//если передвигаем блок, то необходимо заткнуть еще один "мертвый" пиксель
			//поворот прямоугольника неинъективен на мн-ве пикселей
			bool addPixel = false;

			if (yOrtSignum == -1) {
				//смещение по y вверх.
				//"мертвый" пиксель затыкается в первом ряду

				blockSizeICounter = *(blockSizeI);

				for (xi = 0; xi < horizontalWidth; xi++) {

					if (!blockSizeICounter) {
						aY += yOrtSignum;
						bY += yOrtSignum;
						addPixel = true;
						blockSizeI++;
						blockSizeICounter = *(blockSizeI);
					} else {
						addPixel = false;
					}

					blockSizeJ = blockSizes.begin();
					blockSizeJCounter = *(blockSizeJ);

					for (y = aY, x = aX; y <= bY; y++) {

						if (!blockSizeJCounter) {
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
							blockSizeJ++;
							blockSizeJCounter = *(blockSizeJ);
						}

						try {
							putpixel(surface, x, y, color);
						} catch (BadPixelException &ex) {
							cerr << ex.what() << endl;
						}

						blockSizeJCounter--;
					}

					aX += xOrtSignum;
					bX += xOrtSignum;
					blockSizeICounter--;
				}
			} else {
				//смещение по y вверх.
				//"мертвый" пиксель затыкается в последнем ряду

				blockSizeICounter = *(blockSizeI);

				for (xi = 0; xi < horizontalWidth; xi++) {

					if (!blockSizeICounter) {
						aY += yOrtSignum;
						bY += yOrtSignum;
						blockSizeI++;
						blockSizeICounter = *(blockSizeI);
					}

					if (xi != (horizontalWidth - 1) && blockSizeICounter == 1) {
						addPixel = true;
					} else {
						addPixel = false;
					}

					blockSizeJ = blockSizes.begin();
					blockSizeJCounter = *(blockSizeJ);

					for (y = aY, x = aX; y <= bY; y++) {

						if (!blockSizeJCounter) {
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
							blockSizeJ++;
							blockSizeJCounter = *(blockSizeJ);
						}

						try {
							putpixel(surface, x, y, color);
						} catch (BadPixelException &ex) {
							cerr << ex.what() << endl;
						}

						blockSizeJCounter--;
					}

					aX += xOrtSignum;
					bX += xOrtSignum;
					blockSizeICounter--;
				}
			}
		}
	}
}