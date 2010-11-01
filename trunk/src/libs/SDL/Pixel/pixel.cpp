#include <iostream>
#include <sstream>
using namespace std;

#include "pixel.hpp"
#include "../Common/common.hpp"

namespace sdl {

	BadPixelException::BadPixelException(string exceptionString) {
		this->exceptionString = exceptionString;
	}

	const char * BadPixelException::what() const throw () {
		return this->exceptionString.c_str();
	}

	Ui32 getpixel(SDL_Surface *surface, Ui16 x, Ui16 y) throw (BadPixelException &) {
		if (x < 0 || y < 0 || x >= surface->w || y >= surface->h) {
			stringstream error;
			error << "Can't draw pixel at (" << x << ", " << y << ")";
			throw BadPixelException(error.str());
		}

		int bpp = surface->format->BytesPerPixel;
		Ui8 *p = (Ui8 *) surface->pixels + y * surface->pitch + x * bpp;

		switch (bpp) {
			case 1:
				return *p;

			case 2:
				return *(Ui16 *) p;

			case 3:
				if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
					return p[0] << 16 | p[1] << 8 | p[2];
				else
					return p[0] | p[1] << 8 | p[2] << 16;

			case 4:
				return *(Ui32 *) p;

			default:
				return 0;
		}
	}

	void putpixel(SDL_Surface *surface, Ui16 x, Ui16 y, Ui32 color) throw (BadPixelException &) {
		if (x < 0 || y < 0 || x >= surface->w || y >= surface->h) {
			stringstream error;
			error << "Can't draw pixel at (" << x << ", " << y << ")";
			throw BadPixelException(error.str());
		}

		int bpp = surface->format->BytesPerPixel;
		Ui8 *p = (Ui8 *) surface->pixels + y * surface->pitch + x * bpp;

		switch (bpp) {
			case 1:
				*p = color;
				break;

			case 2:
				*(Ui16 *) p = color;
				break;

			case 3:
				if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
					p[0] = (color >> 16) & 0xff;
					p[1] = (color >> 8) & 0xff;
					p[2] = color & 0xff;
				} else {
					p[0] = color & 0xff;
					p[1] = (color >> 8) & 0xff;
					p[2] = (color >> 16) & 0xff;
				}
				break;

			case 4:
				*(Ui32 *) p = color;
				break;
		}
	}
}