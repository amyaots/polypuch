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

#include <Render/Custom/custom.hpp>
using namespace render;

#include <Curve/Bezier/bezier.hpp>
using namespace curve;

#include <Curves/General/general.hpp>
#include <SDL/SDL_keysym.h>
using namespace curves;

#include "Sonne/sonne.hpp"
#include "Earth/earth.hpp"
#include "Mars/mars.hpp"
#include "Rocket/rocket.hpp"

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
	Ui16 count_points = 16;
	Ui16 creation_visualization_delay = 300;
	Ui16 point_radius = 3;

	if (argc != 7) {
		cout << "usage:" << endl;
		cout << "\tpath/to/binary" << endl;
		cout << "\tcount_curves                   (default 5)" << endl;
		cout << "\tcount_points                   (default 16)" << endl;
		cout << "\tcreation_visualization_delay   (default 300)" << endl;
		cout << "\tpoint_radius                   (default 3)" << endl;
	} else {
		count_curves = (Ui16) atoi(argv[1]);
		count_points = (Ui16) atoi(argv[2]);
		creation_visualization_delay = (Ui16) atoi(argv[3]);
		point_radius = (Ui16) atoi(argv[4]);
	}

	//первый аргумент всегда представляет собой абсолютный путь к нашему бинарнику.
	string currentBinary(argv[0]);
	string currentDir = currentBinary.substr(0, currentBinary.find_last_of("/") + 1);

	//<инициализация sdl>

	render::Custom customRender(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITS_PER_PIXEL);
	customRender.setBackground((currentDir + string("bg.png")).c_str());
	customRender.setIcon((currentDir + string("icon.png")).c_str(), "Simple Polygon Render", "Simple Polygon Render");

	//</инициализация sdl>

	//<используемые переменные>

	bool go = true;
	SDL_Event mainEvent;
	SDL_Event* mainEventPointer = &mainEvent;

	Ui32 refreshTime = 1000 / MAX_FPS;

	//центр солнечной системы
	Point center(230, 150);
	Sonne *sonne = new Sonne((currentDir + string("sonne.png")).c_str(), center);
	Earth *earth = new Earth((currentDir + string("earth.png")).c_str(), center, 130, 200);
	Mars *mars = new Mars((currentDir + string("mars.png")).c_str(), center, 90, 300);
	Rocket *rocket = new Rocket((currentDir + string("rocket.png")).c_str(), 50, 300);

	customRender.add(sonne);
	customRender.add(earth);
	customRender.add(mars);

	//<цикл рендеринга>
	go = true;
	Pi time;
	bool rocketFlight;
	while (go) {
		if (SDL_PollEvent(mainEventPointer)) {
			if (mainEventPointer->type == SDL_QUIT) {
				go = false;
			} else if (mainEventPointer->type == SDL_KEYDOWN) {
				switch (mainEventPointer->key.keysym.sym) {
					case SDLK_ESCAPE:
						go = false;
						break;

					case SDLK_SPACE:
						rocket->setFlight(earth->getCurrentPosition(), mars->getPointAfter(300), center);
						customRender.add(rocket);
						rocketFlight = true;
						time = 0;
						break;
				}
			} else {
			}
		} else {
			if(rocketFlight) {
				if(time > 300) {
					customRender.remove(rocket);
					rocketFlight = false;
				}
				time++;
			}
			customRender.reDraw();
			SDL_Delay(refreshTime);
		}
	}
	//</цикл рендеринга>

	delete sonne;
	delete earth;
	delete mars;
	delete rocket;

	return 0;
}