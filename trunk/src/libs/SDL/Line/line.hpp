#ifndef SDL_LINE_HPP
#define SDL_LINE_HPP

#include <SDL.h>
#include "../Common/common.hpp"

//нарисовать линию от точки А до точки Б определенного цвета и ширины

namespace sdl {
    
    void drawLine(
            SDL_Surface *surface,
            Ui16 aX,
            Ui16 aY,
            Ui16 bX,
            Ui16 bY,
            Ui32 color,
            Ui16 width
            );
}

#endif
