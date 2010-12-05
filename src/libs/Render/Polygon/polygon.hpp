#ifndef POLYGON_RENDER_HPP
#define POLYGON_RENDER_HPP

#include <SDL_image.h>

#include "../General/general.hpp"

#include "../../SDL/Common/common.hpp"
using namespace sdl;

#include "../../Polygon/General/general.hpp"

#define ERROR_DELAY 5000

namespace render {

    struct PolygonOptions{
        Ui32 pointColor;
        Ui16 pointRadius;
        Ui32 segmentColor;
        Ui16 segmentWidth;
        bool drawLines;
    };

    struct PointOptions{
        Ui32 pointColor;
        Ui16 pointRadius;
    };

    class Polygon : public General{
    protected:
        vector<pair<polygon::General *, PolygonOptions *> > polygons;
        vector<pair<polygon::Point *, PointOptions *> > points;

    public:
        Polygon(Ui16 width, Ui16 height, Ui16 bitPerPixel) : General(width, height, bitPerPixel) {};
        ~Polygon();

        void add(polygon::General *obj, PolygonOptions *opt);
        void add(polygon::Point *p, PointOptions *opt);

        void reDraw() const;
    };
}

#endif
