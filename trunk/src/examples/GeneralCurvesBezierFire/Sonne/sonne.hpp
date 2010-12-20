#ifndef SONNE_HPP
#define	SONNE_HPP

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

class Sonne : public AbstractRenderObject {
protected:
    SDL_Surface *image;
    Point center;

public:
    Sonne(const char *imagePath, const Point& center);
    ~Sonne();

    void draw(SDL_Surface *screen);
};

#endif