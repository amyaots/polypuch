#include "earth.hpp"

Earth::Earth(const char *imagePath, const Point& center, Pi moving_radius, Pi period) {
	this->image = IMG_Load(imagePath);
	this->center = center;
	this->moving_radius = moving_radius;
	this->period = period;
	this->angleParts = 2 * M_PI / this->period;
	this->time = 0;

	if (!this->image) {
		cerr << "IMG_Load: " << IMG_GetError() << endl;
		SDL_Delay(ERROR_DELAY);
		exit(1);
	}
}

Earth::~Earth() {
	if (!this->image) {
		SDL_FreeSurface(this->image);
	}
}

void Earth::draw(SDL_Surface *screen) {
	f32 angle = this->angleParts * this->time;
	DrawSurface(
			screen,
			this->image,
			center.first + cos(angle) * this->moving_radius - ((f32)this->image->w) / 2,
			center.second + sin(angle) * this->moving_radius - ((f32)this->image->h) / 2,
			0,
			0,
			this->image->w,
			this->image->h
			);
	this->time++;
	if(this->time > this->period) {
		this->time %= this->period;
	}
}

Point Earth::getCurrentPosition() const {
	Point result;
	f32 angle = this->angleParts * this->time;
	result.first = center.first + cos(angle) * this->moving_radius - ((f32)this->image->w) / 2;
	result.second = center.second + sin(angle) * this->moving_radius - ((f32)this->image->h) / 2;
	return result;
}