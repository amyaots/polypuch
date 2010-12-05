#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>

#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <cmath>
using namespace std;

#include <Render/Curves/curves.hpp>
using namespace render;

#include <Curve/General/general.hpp>
using namespace curve;

#include <Curves/General/general.hpp>
using namespace curves;

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 360
#define SCREEN_BITS_PER_PIXEL 32
#define MAX_FPS 30

#define ERROR_DELAY 5000

#define SQUARE_MARGIN 5

int main(int argc, char *argv[]) {

	if (argc < 1) {
		return 1;
	}

	Ui16 count_curves = 5;
	Ui16 creation_visualization_delay = 300;
	Ui16 point_radius = 3;

	if (argc != 7) {
		cout << "usage:" << endl;
		cout << "\tpath/to/binary" << endl;
		cout << "\tcount_curves                   (default 5)" << endl;
		cout << "\tcreation_visualization_delay   (default 300)" << endl;
		cout << "\tpoint_radius                   (default 3)" << endl;
	} else {
		count_curves = (Ui16) atoi(argv[1]);
		creation_visualization_delay = (Ui16) atoi(argv[2]);
		point_radius = (Ui16) atoi(argv[3]);
	}

	//первый аргумент всегда представляет собой абсолютный путь к нашему бинарнику.
	string currentBinary(argv[0]);
	string currentDir = currentBinary.substr(0, currentBinary.find_last_of("/") + 1);

	//<инициализация sdl>

	render::Curves curvesRender(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITS_PER_PIXEL);
	curvesRender.setBackground((currentDir + string("bg.png")).c_str());
	curvesRender.setIcon((currentDir + string("icon.png")).c_str(), "Simple Polygon Render", "Simple Polygon Render");

	//</инициализация sdl>

	//<используемые переменные>

	bool go = true;
	SDL_Event mainEvent;
	SDL_Event* mainEventPointer = &mainEvent;

	Ui32 refreshTime = 1000 / MAX_FPS;

	//цвета
	Ui32 black = curvesRender.getRGBColor(0, 0, 0);
	Ui32 green = curvesRender.getRGBColor(0, 255, 0);
	Ui32 red = curvesRender.getRGBColor(255, 0, 0);
	Ui32 yellow = curvesRender.getRGBColor(255, 255, 0);

	//добавим кучу кривых
	CurveOptions *co = new CurveOptions();
	co->curveColor = green;
	co->pointColor = black;
	co->pointRadius = point_radius;

	curves::General *curves = new curves::General();

	curvesRender.add(curves, co);

	//<цикл рендеринга>
	Ui16 i;
	i = 0;
	srand(time(NULL));
	Point firstPoint, secondPoint;
	go = true;
	while (go) {
		if (SDL_PollEvent(mainEventPointer)) {
			if (mainEventPointer->type == SDL_QUIT) {
				go = false;
			} else if (mainEventPointer->type == SDL_KEYDOWN) {
				switch (mainEventPointer->key.keysym.sym) {
					case SDLK_ESCAPE:
						go = false;
						break;
				}
			} else {
			}
		} else {
			firstPoint.first = SQUARE_MARGIN + rand() % (SCREEN_WIDTH - 2 * SQUARE_MARGIN);
			firstPoint.second = SQUARE_MARGIN + rand() % (SCREEN_HEIGHT - 2 * SQUARE_MARGIN);

			secondPoint.first = SQUARE_MARGIN + rand() % (SCREEN_WIDTH - 2 * SQUARE_MARGIN);
			secondPoint.second = SQUARE_MARGIN + rand() % (SCREEN_HEIGHT - 2 * SQUARE_MARGIN);

			curve::General curve;

			curve.approximate(firstPoint, secondPoint);
			if(curves->add(curve)) {
				curvesRender.reDraw();
				SDL_Delay(creation_visualization_delay);
				i++;
			}

			if (i > count_curves) {
				go = false;
			}
		}
	}
	//</цикл рендеринга>

	//<цикл рендеринга>
	go = true;
	while (go) {
		if (SDL_PollEvent(mainEventPointer)) {
			if (mainEventPointer->type == SDL_QUIT) {
				go = false;
			} else if (mainEventPointer->type == SDL_KEYDOWN) {
				switch (mainEventPointer->key.keysym.sym) {
					case SDLK_ESCAPE:
						go = false;
						break;
				}
			} else {
			}
		} else {
			SDL_Delay(refreshTime);
		}
	}
	//</цикл рендеринга>

	delete curves;
	delete co;

	return 0;
}