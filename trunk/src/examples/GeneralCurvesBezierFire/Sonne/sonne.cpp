#include "Sonne.hpp"

Sonne::Sonne(const char *imagePath, const Point& center) {
	this->image = IMG_Load(imagePath);
	this->center = center;
	if (!this->image) {
		cerr << "IMG_Load: " << IMG_GetError() << endl;
		SDL_Delay(ERROR_DELAY);
		exit(1);
	}
}

Sonne::~Sonne() {
	if (!this->image) {
		SDL_FreeSurface(this->image);
	}
}

void Sonne::draw(SDL_Surface *screen) {
	DrawSurface(
			screen,
			this->image,
			center.first - ((f32)this->image->w) / 2,
			center.second - ((f32)this->image->h) / 2,
			0,
			0,
			this->image->w,
			this->image->h
			);
}