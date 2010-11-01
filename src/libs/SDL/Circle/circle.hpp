#ifndef SDL_CIRCLE_HPP
#define SDL_CIRCLE_HPP

#include <SDL.h>
#include "../Common/common.hpp"

//нарисовать линию от точки А до точки Б определенного цвета и ширины

namespace sdl {

    void drawCircle(
            SDL_Surface *surface,
            Ui16 x,
            Ui16 y,
            Ui32 color,
            Ui16 radius
            );
}
#endif
