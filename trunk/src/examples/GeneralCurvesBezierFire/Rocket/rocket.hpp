#ifndef ROCKET_HPP
#define	ROCKET_HPP

#include <math.h>

#include <iostream>
using namespace std;

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../../../libs/Render/AbstractRenderObject/abstractRenderObject.hpp"

#include "../../../libs/SDL/Common/common.hpp"
using namespace sdl;

#include "../../../libs/Polygon/General/general.hpp"
using namespace polygon;

#include "../../../libs/Curve/Bezier/bezier.hpp"
using namespace curve;

#define ERROR_DELAY 5000

class Rocket : public AbstractRenderObject {
protected:
    SDL_Surface *image;
    Pi moving_radius;
    Pi period;
    f32 angleParts;
    Pi time;
    Bezier curve;

public:
    Rocket(const char *imagePath, Pi moving_radius, Pi period);
    ~Rocket();

    void draw(SDL_Surface *screen);

    void setFlight(const Point& from, const Point& to, const Point& sonneCenter);
};

#endif