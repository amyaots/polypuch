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
	Ui32 yellow = polygonRender.getRGBColor(255, 255, 0);

	PolygonOptions *polyConvexOpt1 = new PolygonOptions();
	polyConvexOpt1->pointColor = green;
	polyConvexOpt1->pointRadius = point_radius;
	polyConvexOpt1->segmentColor = green;
	polyConvexOpt1->segmentWidth = segment_width;
	polyConvexOpt1->drawLines = true;

	PolygonOptions *polyConvexOpt2 = new PolygonOptions();
	polyConvexOpt2->pointColor = yellow;
	polyConvexOpt2->pointRadius = point_radius;
	polyConvexOpt2->segmentColor = yellow;
	polyConvexOpt2->segmentWidth = segment_width;
	polyConvexOpt2->drawLines = true;
	
	PolygonOptions *polyConvexOpt3 = new PolygonOptions();
	polyConvexOpt3->pointColor = red;
	polyConvexOpt3->pointRadius = point_radius;
	polyConvexOpt3->segmentColor = red;
	polyConvexOpt3->segmentWidth = segment_width;
	polyConvexOpt3->drawLines = true;

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
	random_points.push_back(Point(50, 50));
	random_points.push_back(Point(50, 250));
	random_points.push_back(Point(250, 250));
	random_points.push_back(Point(250, 50));
	 * */

	//добавим полигон
	Convex *polyConvex1 = new Convex(random_points, polygon::GRAHAM);
	polygonRender.add(polyConvex1, polyConvexOpt1);

	//создаем вектор точек
	random_points.clear();
	i = 0;
	for (i = 0; i < count_points; i++) {
		Point newPoint;
		newPoint.first = 5 + rand() % (SCREEN_WIDTH - 10);
		newPoint.second = 5 + rand() % (SCREEN_HEIGHT - 10);
		random_points.push_back(newPoint);
	}

	/*
	random_points.clear();
	random_points.push_back(Point(100, 220));
	random_points.push_back(Point(400, 10));
	random_points.push_back(Point(400, 350));
	 * */
	
	//добавим полигон
	Convex *polyConvex2 = new Convex(random_points, polygon::GRAHAM);
	polygonRender.add(polyConvex2, polyConvexOpt2);

	//добавим пересечение
	Convex intersect = polyConvex1->intersect(*polyConvex2);
	polygonRender.add(&intersect, polyConvexOpt3);
	
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

	delete polyConvex1;
	delete polyConvex2;
	delete polyConvexOpt1;
	delete polyConvexOpt2;
	delete polyConvexOpt3;

	return 0;
}