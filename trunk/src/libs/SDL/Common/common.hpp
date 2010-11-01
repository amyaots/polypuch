#ifndef SDL_COMMON_HPP
#define SDL_COMMON_HPP

#include <SDL.h>
#include "limits.h"
#include "float.h"

namespace sdl {

    typedef signed char Si8;
    #define Si8_Min SCHAR_MIN
    #define Si8_Max SCHAR_MAX

    typedef unsigned char Ui8;
    #define Ui8_Min 0
    #define Ui8_Max UCHAR_MAX

    typedef short Si16;
    #define Si16_Min SHRT_MIN
    #define Si16_Max SHRT_MAX

    typedef unsigned short Ui16;
    #define Ui16_Min 0
    #define Ui16_Max USHRT_MAX

    typedef int Si32;
    #define Si32_Min INT_MAX
    #define Si32_Max INT_MIN

    typedef unsigned Ui32;
    #define Ui32_Min 0
    #define Ui32_Max UINT_MAX

    typedef float f32;
    #define f32_Min FLT_MIN
    #define f32_Max FLT_MAX

    typedef double f64;
    #define f64_Min DBL_MIN
    #define f64_Max DLB_MAX

    //заблокировать поверхность
    void Slock(SDL_Surface *screen);

    //раззаблокировать поверхность
    void Sulock(SDL_Surface *screen);

    //нарисовать часть поверхности на другую
    void DrawSurface(
            SDL_Surface *screen,
            SDL_Surface *image,
            Ui16 x,
            Ui16 y,
            Ui16 srcX,
            Ui16 srcY,
            Ui16 width,
            Ui16 height
            );

}
#endif
