#ifndef SDL_PIXEL_HPP
#define SDL_PIXEL_HPP

#include <SDL.h>
#include <string>
using namespace std;

#include "../Common/common.hpp"

namespace sdl {

    class BadPixelException : public exception {
    private:
        string exceptionString;

    public:
        BadPixelException(string);

        virtual ~BadPixelException() throw () {
        };
        virtual const char * what() const throw ();
    };

    //получить цвет пикселя
    Ui32 getpixel(SDL_Surface *surface, Ui16 x, Ui16 y) throw (BadPixelException &);

    //установить цвет пикселя
    void putpixel(SDL_Surface *surface, Ui16 x, Ui16 y, Ui32 color) throw (BadPixelException &);
}

#endif
