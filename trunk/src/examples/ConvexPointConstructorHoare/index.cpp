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
using namespace std;

#include <SDL/Circle/circle.hpp>
#include <SDL/Common/common.hpp>
#include <SDL/Pixel/pixel.hpp>
#include <SDL/Line/line.hpp>
using namespace sdl;

#include <Polygon/General/general.hpp>
#include <Polygon/Convex/convex.hpp>
using namespace polygon;

#include <Render/Polygon/polygon.hpp>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 360
#define SCREEN_BITS_PER_PIXEL 32
#define MAX_FPS 30

#define ERROR_DELAY 5000

int main(int argc, char *argv[]) {

	if (argc < 1) {
		return 1;
	}

	Ui16 count_points = 20;
	Ui16 visualization_delay = 0;
	Ui16 point_radius = 3;
	Ui16 segment_width = 2;

	if (argc != 5) {
		cout << "usage:" << endl;
		cout << "\tpath/to/binary" << endl;
		cout << "\tcount_points          (default 20)" << endl;
		cout << "\tvisualization_delay   (default 0)" << endl;
		cout << "\tpoint_radius          (default 3)" << endl;
		cout << "\tsegment_width         (default 2)" << endl;
	} else {
		count_points = (Ui16) atoi(argv[1]);
		visualization_delay = (Ui16) atoi(argv[2]);
		point_radius = (Ui16) atoi(argv[3]);
		segment_width = (Ui16) atoi(argv[4]);
	}

	//первый аргумент всегда представляет собой абсолютный путь к нашему бинарнику.
	string currentBinary(argv[0]);
	string currentDir = currentBinary.substr(0, currentBinary.find_last_of("/") + 1);

	//<инициализация sdl>

	Polygon polygonRender(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITS_PER_PIXEL);
	polygonRender.setBackground((currentDir + string("bg.png")).c_str());
	polygonRender.setIcon((currentDir + string("icon.png")).c_str(), "Convex Polygon Render", "Convex Polygon Render");

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

	//создаем вектор точек
	vector<Point> random_points;
	Ui16 i;
	srand(time(NULL));
	i = 0;
	for (i = 0; i < count_points; i++) {
		Point newPoint;
		newPoint.first = 5 + rand() % (SCREEN_WIDTH - 10);
		newPoint.second = 5 + rand() % (SCREEN_HEIGHT - 10);
		random_points.push_back(newPoint);
	}

	/*
	vector<Point> random_points;
	random_points.push_back(Point(250, 150));
	random_points.push_back(Point(100, 300));
	random_points.push_back(Point(320, 10));
	random_points.push_back(Point(350, 350));
	 * */

	//добавим полигон
	Convex *polyConvex = new Convex(random_points, polygon::HOARE);

	PolygonOptions *polyConvexOpt = new PolygonOptions();
	polyConvexOpt->pointColor = green;
	polyConvexOpt->pointRadius = point_radius;
	polyConvexOpt->segmentColor = black;
	polyConvexOpt->segmentWidth = segment_width;
	polyConvexOpt->drawLines = true;

	polygonRender.add(polyConvex, polyConvexOpt);

	//нарисуем все точки
	polygon::General *polyGeneral = new polygon::General(random_points);

	PolygonOptions *polyGeneralOpt = new PolygonOptions();
	polyGeneralOpt->pointColor = green;
	polyGeneralOpt->pointRadius = point_radius;
	polyGeneralOpt->segmentColor = black;
	polyGeneralOpt->segmentWidth = segment_width;
	polyGeneralOpt->drawLines = false;

	polygonRender.add(polyGeneral, polyGeneralOpt);
	
	polygonRender.reDraw();

	//</используемые переменные>

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

	delete polyConvex;
	delete polyGeneral;
	delete polyConvexOpt;
	delete polyGeneralOpt;

	return 0;
}