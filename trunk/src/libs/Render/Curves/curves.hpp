#ifndef CURVES_RENDER_HPP
#define CURVES_RENDER_HPP

#include <SDL_image.h>

#include "../General/general.hpp"

#include "../../SDL/Common/common.hpp"
using namespace sdl;

#include "../../Curves/General/general.hpp"

#define ERROR_DELAY 5000

namespace render {

    struct CurveOptions{
        Ui32 pointColor;
        Ui16 pointRadius;
        Ui32 curveColor;
    };

    struct PointOptions{
        Ui32 pointColor;
        Ui16 pointRadius;
    };

    class Curves : public General{
    protected:
        vector<pair<curves::General *, CurveOptions *> > curves;
        vector<pair<polygon::Point, PointOptions *> > points;

    public:
        Curves(Ui16 width, Ui16 height, Ui16 bitPerPixel) : General(width, height, bitPerPixel) {};
        ~Curves();

        void add(curves::General *obj, CurveOptions *opt);
        void add(polygon::Point p, PointOptions *opt);
        
        void reDraw() const;
    };
}

#endif
