#ifndef GENERAL_RENDER_HPP
#define GENERAL_RENDER_HPP

#include <SDL_image.h>

#include "../../SDL/Common/common.hpp"
using namespace sdl;

#define ERROR_DELAY 5000

namespace render {

    class General{
    protected:
        SDL_Surface *screen;
        SDL_Surface *back;
        SDL_Surface *icon;

        Ui16 width;
        Ui16 height;

    public:
        General(Ui16 width, Ui16 height, Ui16 bitPerPixel);
        virtual ~General();

        void setBackground(const char *backFile);
        void setIcon(const char *iconFile, const char *title, const char *miniTitle);

        virtual void reDraw() const;

        Ui32 getRGBColor(Ui8 R, Ui8 G, Ui8 B);
    };
}

#endif
