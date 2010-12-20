#include "rocket.hpp"

Rocket::Rocket(const char *imagePath, Pi moving_radius, Pi period) {
	this->image = IMG_Load(imagePath);
	this->period = period;
	this->moving_radius = moving_radius;
	this->angleParts = 2 * M_PI / this->period;
	this->time = 0;

	if (!this->image) {
		cerr << "IMG_Load: " << IMG_GetError() << endl;
		SDL_Delay(ERROR_DELAY);
		exit(1);
	}
}

Rocket::~Rocket() {
	if (!this->image) {
		SDL_FreeSurface(this->image);
	}
}

void Rocket::draw(SDL_Surface *screen) {
	Point currentPoint = this->curve.getPoint((f32)this->time / this->period);
	DrawSurface(
			screen,
			this->image,
			currentPoint.first - ((f32)this->image->w) / 2,
			currentPoint.second - ((f32)this->image->h) / 2,
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

void Rocket::setFlight(const Point& from, const Point& to, const Point& sonneCenter) {
	vector<Point> controlPoints;

	controlPoints.push_back(from);

	f32 vectorX = from.first - sonneCenter.first;
	f32 vectorY = from.second - sonneCenter.second;
	f32 vectorLength = sqrt(vectorX * vectorX + vectorY * vectorY);
	vectorX /= vectorLength;
	vectorY /= vectorLength;

	Point currentPoint;

	currentPoint.first = sonneCenter.first + vectorX * this->moving_radius;
	currentPoint.second = sonneCenter.second + vectorY * this->moving_radius;

	//controlPoints.push_back(currentPoint);

	currentPoint.first = sonneCenter.first + (-vectorY) * this->moving_radius * 3;
	currentPoint.second = sonneCenter.second + (vectorX) * this->moving_radius * 3;

	controlPoints.push_back(currentPoint);

	currentPoint.first = sonneCenter.first + (-vectorX) * this->moving_radius * 3;
	currentPoint.second = sonneCenter.second + (-vectorY) * this->moving_radius * 3;

	controlPoints.push_back(currentPoint);

	currentPoint.first = sonneCenter.first + (vectorY) * this->moving_radius * 3;
	currentPoint.second = sonneCenter.second + (-vectorX) * this->moving_radius * 3;

	controlPoints.push_back(currentPoint);

	

	currentPoint.first = sonneCenter.first + vectorX * this->moving_radius * 3;
	currentPoint.second = sonneCenter.second + vectorY * this->moving_radius * 3;

	controlPoints.push_back(currentPoint);

	currentPoint.first = sonneCenter.first + (-vectorY) * this->moving_radius * 3;
	currentPoint.second = sonneCenter.second + (vectorX) * this->moving_radius * 3;

	controlPoints.push_back(currentPoint);

	currentPoint.first = sonneCenter.first + (-vectorX) * this->moving_radius * 3;
	currentPoint.second = sonneCenter.second + (-vectorY) * this->moving_radius * 3;

	controlPoints.push_back(currentPoint);

	currentPoint.first = sonneCenter.first + (vectorY) * this->moving_radius * 3;
	currentPoint.second = sonneCenter.second + (-vectorX) * this->moving_radius * 3;

	controlPoints.push_back(currentPoint);

	

	controlPoints.push_back(to);

	vector<Point>::iterator it;
	for(it = controlPoints.begin(); it != controlPoints.end(); it++) {
		cout << (*it).first << ", " << (*it).second << endl;
	}
	cout << endl;

	this->curve.approximate(controlPoints);
	this->time = 0;
}