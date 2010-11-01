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

#include <SDL/Circle/circle.hpp>
#include <SDL/Common/common.hpp>
#include <SDL/Pixel/pixel.hpp>
#include <SDL/Line/line.hpp>
using namespace sdl;

#include <Segments/General/general.hpp>
using namespace segments;

#include <Render/Polygon/polygon.hpp>
using namespace render;

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

	Ui16 count_segments = 5;
	Ui16 count_beams = 50;
	Ui16 creation_visualization_delay = 0;
	Ui16 point_radius = 3;
	Ui16 segment_width = 2;
	Ui16 beams_visualization_delay = 200;

	if (argc != 7) {
		cout << "usage:" << endl;
		cout << "\tpath/to/binary" << endl;
		cout << "\tcount_points                   (default 100)" << endl;
		cout << "\tcreation_visualization_delay   (default 0)" << endl;
		cout << "\tpoint_radius                   (default 3)" << endl;
		cout << "\tsegment_width                  (default 2)" << endl;
		cout << "\tcount_beams                    (default 100)" << endl;
		cout << "\tbeams_visualization_delay      (default 0)" << endl;
	} else {
		count_segments = (Ui16) atoi(argv[1]);
		creation_visualization_delay = (Ui16) atoi(argv[2]);
		point_radius = (Ui16) atoi(argv[3]);
		segment_width = (Ui16) atoi(argv[4]);
		count_beams = (Ui16) atoi(argv[5]);
		beams_visualization_delay = (Ui16) atoi(argv[6]);
	}

	//первый аргумент всегда представляет собой абсолютный путь к нашему бинарнику.
	string currentBinary(argv[0]);
	string currentDir = currentBinary.substr(0, currentBinary.find_last_of("/") + 1);

	//<инициализация sdl>

	Polygon polygonRender(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITS_PER_PIXEL);
	polygonRender.setBackground((currentDir + string("bg.png")).c_str());
	polygonRender.setIcon((currentDir + string("icon.png")).c_str(), "Simple Polygon Render", "Simple Polygon Render");

	//</инициализация sdl>

	//<используемые переменные>

	bool go = true;
	SDL_Event mainEvent;
	SDL_Event* mainEventPointer = &mainEvent;

	Ui32 refreshTime = 1000 / MAX_FPS;

	//цвета
	Ui32 black = polygonRender.getRGBColor(0, 0, 0);
	Ui32 green = polygonRender.getRGBColor(0, 255, 0);
	Ui32 red = polygonRender.getRGBColor(255, 0, 0);
	Ui32 yellow = polygonRender.getRGBColor(255, 255, 0);

	//добавим кучу отрезков
	segments::General *segments = new segments::General();

	SegmentsOptions *segOpt = new SegmentsOptions();
	segOpt->pointColor = green;
	segOpt->pointRadius = point_radius;
	segOpt->segmentColor = black;
	segOpt->segmentWidth = segment_width;

	polygonRender.add(segments, segOpt);

	//добавим еще одну кучу отрезков, но другого цвета
	//это будут лучики
	segments::General *segmentsBeams = new segments::General();

	SegmentsOptions *segOptBeams = new SegmentsOptions();
	segOptBeams->pointColor = red;
	segOptBeams->pointRadius = point_radius;
	segOptBeams->segmentColor = yellow;
	segOptBeams->segmentWidth = segment_width;

	polygonRender.add(segmentsBeams, segOptBeams);

	//</используемые переменные>

	//<цикл рендеринга>
	//включаем работу алгоритма в стандартный цикл sdl
	//во время работы алгоритма приложение будет отзываться на любые системные события
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

			segments->add(firstPoint, secondPoint);
			polygonRender.reDraw();
			SDL_Delay(creation_visualization_delay);
			i++;

			if (i > count_segments) {
				go = false;
			}
		}
	}
	//</цикл рендеринга>

	/*
	firstPoint.first = 100;
	firstPoint.second = 100;

	secondPoint.first = 300;
	secondPoint.second = 150;
	 * */

	segments->add(firstPoint, secondPoint);

	//создадим ограничивающий прямоугольник
	Point leftTop(SQUARE_MARGIN, SQUARE_MARGIN);
	Point rightTop(SCREEN_WIDTH - 2 * SQUARE_MARGIN, SQUARE_MARGIN);
	Point leftDown(SQUARE_MARGIN, SCREEN_HEIGHT - 2 * SQUARE_MARGIN);
	Point rightDown(SCREEN_WIDTH - 2 * SQUARE_MARGIN, SCREEN_HEIGHT - 2 * SQUARE_MARGIN);

	//направляющий вектор создаем по двум точкам
	Point currentPoint(SQUARE_MARGIN + rand() % (SCREEN_WIDTH - 2 * SQUARE_MARGIN), SQUARE_MARGIN + rand() % (SCREEN_HEIGHT - 2 * SQUARE_MARGIN));
	Point toPoint(SQUARE_MARGIN + rand() % (SCREEN_WIDTH - 2 * SQUARE_MARGIN), SQUARE_MARGIN + rand() % (SCREEN_HEIGHT - 2 * SQUARE_MARGIN));
	/*
	Point currentPoint(10, 340);
	Point toPoint(200, 120);
	 * */
	f32 length = sqrt((currentPoint.first - toPoint.first) * (currentPoint.first - toPoint.first) + (currentPoint.second - toPoint.second) * (currentPoint.second - toPoint.second));

	f32 vX = (toPoint.first - currentPoint.first) / length;
	f32 vY = (toPoint.second - currentPoint.second) / length;

	//<цикл рендеринга>
	//включаем работу алгоритма в стандартный цикл sdl
	//во время работы алгоритма приложение будет отзываться на любые системные события
	i = 0;
	go = true;
	vector<Segment> ignore;
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
			segmentsBeams->add(segments->beam(currentPoint, vX, vY, leftTop, rightTop, rightDown, leftDown, ignore));
			polygonRender.reDraw();
			SDL_Delay(beams_visualization_delay);
			i++;

			if (i > count_beams) {
				go = false;
			}
		}
	}
	//</цикл рендеринга>

	/*
	segmentsBeams->add(segments->beam(currentPoint, vX, vY, leftTop, rightTop, rightDown, leftDown, ignore));
	polygonRender.reDraw();
	segmentsBeams->add(segments->beam(currentPoint, vX, vY, leftTop, rightTop, rightDown, leftDown, ignore));
	polygonRender.reDraw();
	segmentsBeams->add(segments->beam(currentPoint, vX, vY, leftTop, rightTop, rightDown, leftDown, ignore));
	polygonRender.reDraw();
	 * */

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

	delete segments;
	delete segOpt;
	delete segmentsBeams;
	delete segOptBeams;

	return 0;
}