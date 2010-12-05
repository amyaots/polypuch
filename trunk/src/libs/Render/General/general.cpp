#include <iostream>
#include <sstream>
using namespace std;

#include "general.hpp"
#include "../../SDL/Line/line.hpp"
#include "../../SDL/Circle/circle.hpp"

namespace render {

	General::General(Ui16 width, Ui16 height, Ui16 bitPerPixel) {
		this->screen = NULL;
		this->back = NULL;
		this->icon = NULL;

		this->width = width;
		this->height = height;

		if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_ASYNCBLIT) < 0) {
			cerr << "Unable to init SDL: " << SDL_GetError() << endl;
			SDL_Delay(ERROR_DELAY);
			exit(1);
		}

		this->screen = SDL_SetVideoMode(this->width, this->height, bitPerPixel, SDL_HWSURFACE | SDL_DOUBLEBUF);
		if (this->screen == NULL) {
			cerr << "Unable to set " << this->width << "x" << this->height << ":" << bitPerPixel << " video: " << SDL_GetError() << endl;
			SDL_Delay(ERROR_DELAY);
			exit(1);
		} else {
			cout << "Set " << this->width << "x" << this->height << ":" << bitPerPixel << " video" << endl;
		}
	}

	General::~General() {
		if (!this->screen) {
			SDL_FreeSurface(this->screen);
		}

		if (!this->back) {
			SDL_FreeSurface(this->back);
		}

		if (!this->back) {
			SDL_FreeSurface(this->back);
		}
	}

	void General::reDraw() const {
		Slock(this->screen);

		DrawSurface(this->screen, this->back, 0, 0, 0, 0, this->back->w, this->back->h);

		Sulock(this->screen);

		SDL_Flip(this->screen);
	}

	void General::setBackground(const char *backFile) {
		this->back = IMG_Load(backFile);
		if (!this->back) {
			cerr << "IMG_Load: " << IMG_GetError() << endl;
			SDL_Delay(ERROR_DELAY);
			exit(1);
		}
	}

	void General::setIcon(const char *iconFile, const char *title, const char *miniTitle) {
		SDL_WM_SetCaption(title, miniTitle);
		this->icon = IMG_Load(iconFile);
		if (!this->icon) {
			cerr << "IMG_Load: " << IMG_GetError() << endl;
			SDL_Delay(ERROR_DELAY);
			exit(1);
		}
		SDL_WM_SetIcon(this->icon, NULL);
	}

	Ui32 General::getRGBColor(Ui8 R, Ui8 G, Ui8 B) {
		return SDL_MapRGB(this->screen->format, R, G, B);
	}
}