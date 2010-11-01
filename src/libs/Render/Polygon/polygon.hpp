#ifndef POLYGON_RENDER_HPP
#define POLYGON_RENDER_HPP

#include <SDL_image.h>

#include "../../SDL/Common/common.hpp"
using namespace sdl;

#include "../../Polygon/General/general.hpp"
#include "../../Segments/General/general.hpp"

#define ERROR_DELAY 5000

namespace render {

    struct PolygonOptions{
        Ui32 pointColor;
        Ui16 pointRadius;
        Ui32 segmentColor;
        Ui16 segmentWidth;
        bool drawLines;
    };

    struct SegmentsOptions{
        Ui32 pointColor;
        Ui16 pointRadius;
        Ui32 segmentColor;
        Ui16 segmentWidth;
    };

    struct PointOptions{
        Ui32 pointColor;
        Ui16 pointRadius;
    };

    class Polygon{
    private:
        SDL_Surface *screen;
        SDL_Surface *back;
        SDL_Surface *icon;

        Ui16 width;
        Ui16 height;

        vector<pair<polygon::General *, PolygonOptions *> > polygons;
        vector<pair<segments::General *, SegmentsOptions *> > segments;
        vector<pair<Point *, PointOptions *> > points;

    public:
        Polygon(Ui16 width, Ui16 height, Ui16 bitPerPixel);
        ~Polygon();

        void setBackground(const char *backFile);
        void setIcon(const char *iconFile, const char *title, const char *miniTitle);

        void add(polygon::General *obj, PolygonOptions *opt);
        void add(Point *p, PointOptions *opt);
        void add(segments::General *s, SegmentsOptions *opt);

        void reDraw() const;

        Ui32 getRGBColor(Ui8 R, Ui8 G, Ui8 B);
    };
}

#endif
