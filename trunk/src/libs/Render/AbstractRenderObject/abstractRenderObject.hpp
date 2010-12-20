#ifndef ABSTRACT_RENDER_OBJECT_HPP
#define ABSTRACT_RENDER_OBJECT_HPP

#include <SDL_image.h>

#include "../../SDL/Common/common.hpp"
using namespace sdl;

class AbstractRenderObject {
public:

    virtual void draw(SDL_Surface *screen) = 0;
};

#endif
