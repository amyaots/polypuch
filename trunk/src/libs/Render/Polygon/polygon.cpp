#include <iostream>
#include <sstream>
using namespace std;

#include "polygon.hpp"
#include "../../SDL/Line/line.hpp"
#include "../../SDL/Circle/circle.hpp"

namespace render {

	Polygon::Polygon(Ui16 width, Ui16 height, Ui16 bitPerPixel) {
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

	Polygon::~Polygon() {
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

	void Polygon::reDraw() const {
		Slock(this->screen);

		DrawSurface(this->screen, this->back, 0, 0, 0, 0, this->back->w, this->back->h);

		vector<pair<General *, PolygonOptions *> >::const_iterator it;
		pair<General *, PolygonOptions *> currentPair;
		for (it = this->polygons.begin(); it != this->polygons.end(); it++) {
			currentPair = *it;
			if (currentPair.first) {
				currentPair.first->draw(
						this->screen,
						currentPair.second->pointColor,
						currentPair.second->pointRadius,
						currentPair.second->segmentColor,
						currentPair.second->segmentWidth,
						currentPair.second->drawLines
						);
			}
		}

		vector<pair<Point *, PointOptions *> >::const_iterator jt;
		pair<Point *, PointOptions *> currentPointPair;
		for (jt = this->points.begin(); jt != this->points.end(); jt++) {
			currentPointPair = *jt;
			if (currentPointPair.first) {
				drawCircle(
						this->screen,
						currentPointPair.first->first,
						currentPointPair.first->second,
						currentPointPair.second->pointColor,
						currentPointPair.second->pointRadius
						);
			}
		}

		vector<pair<segments::General *, SegmentsOptions *> >::const_iterator kt;
		pair<segments::General *, SegmentsOptions *> currentSegmentsPair;
		for (kt = this->segments.begin(); kt != this->segments.end(); kt++) {
			currentSegmentsPair = *kt;
			if (currentSegmentsPair.first) {
				currentSegmentsPair.first->draw(
						this->screen,
						currentSegmentsPair.second->pointColor,
						currentSegmentsPair.second->pointRadius,
						currentSegmentsPair.second->segmentColor,
						currentSegmentsPair.second->segmentWidth
						);
			}
		}

		Sulock(this->screen);

		SDL_Flip(this->screen);
	}

	void Polygon::setBackground(const char *backFile) {
		this->back = IMG_Load(backFile);
		if (!this->back) {
			cerr << "IMG_Load: " << IMG_GetError() << endl;
			SDL_Delay(ERROR_DELAY);
			exit(1);
		}
	}

	void Polygon::setIcon(const char *iconFile, const char *title, const char *miniTitle) {
		SDL_WM_SetCaption(title, miniTitle);
		this->icon = IMG_Load(iconFile);
		if (!this->icon) {
			cerr << "IMG_Load: " << IMG_GetError() << endl;
			SDL_Delay(ERROR_DELAY);
			exit(1);
		}
		SDL_WM_SetIcon(this->icon, NULL);
	}

	void Polygon::add(polygon::General *obj, PolygonOptions *opt) {
		this->polygons.push_back(pair<General *, PolygonOptions *> (obj, opt));
	}

	void Polygon::add(Point *p, PointOptions *opt) {
		this->points.push_back(pair<Point *, PointOptions *> (p, opt));
	}

	void Polygon::add(segments::General *s, SegmentsOptions *opt) {
		this->segments.push_back(pair<segments::General *, SegmentsOptions *> (s, opt));
	}

	Ui32 Polygon::getRGBColor(Ui8 R, Ui8 G, Ui8 B) {
		return SDL_MapRGB(this->screen->format, R, G, B);
	}
}