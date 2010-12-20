#ifndef CUSTOM_RENDER_HPP
#define CUSTOM_RENDER_HPP

#include <SDL_image.h>

#include <vector>
using namespace std;

#include "../../SDL/Common/common.hpp"
using namespace sdl;

#include "../General/general.hpp"
#include "../AbstractRenderObject/abstractRenderObject.hpp"

#define ERROR_DELAY 5000

namespace render {

    class Custom : public General{
    protected:
        vector<AbstractRenderObject *> objects;

    public:
        Custom(Ui16 width, Ui16 height, Ui16 bitPerPixel) : General(width, height, bitPerPixel) {};
        ~Custom();

        void add(AbstractRenderObject* obj);
        void remove(AbstractRenderObject* obj);

        void reDraw() const;
    };
}

#endif
