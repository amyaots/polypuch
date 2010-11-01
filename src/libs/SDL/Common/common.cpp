#include <SDL.h>
#include "common.hpp"

namespace sdl {

	void Slock(SDL_Surface *screen) {
		if (SDL_MUSTLOCK(screen)) {
			if (SDL_LockSurface(screen) < 0) {
				return;
			}
		}
	}

	void Sulock(SDL_Surface *screen) {
		if (SDL_MUSTLOCK(screen)) {
			SDL_UnlockSurface(screen);
		}
	}

	void DrawSurface(
			SDL_Surface *screen,
			SDL_Surface *image,
			Ui16 x,
			Ui16 y,
			Ui16 srcX,
			Ui16 srcY,
			Ui16 width,
			Ui16 height
			) {
		SDL_Rect dest;
		dest.x = x;
		dest.y = y;

		SDL_Rect src;
		src.x = srcX;
		src.y = srcY;
		src.w = width;
		src.h = height;

		SDL_BlitSurface(image, &src, screen, &dest);
	}
}