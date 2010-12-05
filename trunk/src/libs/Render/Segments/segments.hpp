#ifndef SEGMENT_RENDER_HPP
#define SEGMENT_RENDER_HPP

#include <SDL_image.h>

#include "../General/general.hpp"

#include "../../SDL/Common/common.hpp"
using namespace sdl;

#include "../../Segments/General/general.hpp"

#define ERROR_DELAY 5000

namespace render {

    struct SegmentsOptions{
        Ui32 pointColor;
        Ui16 pointRadius;
        Ui32 segmentColor;
        Ui16 segmentWidth;
    };

    class Segments : public General{
    protected:
        vector<pair<segments::General *, SegmentsOptions *> > segments;
        
    public:
        Segments(Ui16 width, Ui16 height, Ui16 bitPerPixel) : General(width, height, bitPerPixel) {}
        ~Segments();

        void add(segments::General *s, SegmentsOptions *opt);

        void reDraw() const;
    };
}

#endif
