#ifndef EARTH_HPP
#define	EARTH_HPP

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

#define ERROR_DELAY 5000

class Earth : public AbstractRenderObject {
protected:
    SDL_Surface *image;
    Point center;
    Pi moving_radius;
    Pi period;
    f32 angleParts;
    Pi time;

public:
    Earth(const char *imagePath, const Point& center, Pi moving_radius, Pi period);
    ~Earth();

    void draw(SDL_Surface *screen);
    Point getCurrentPosition() const;
};

#endif