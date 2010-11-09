#ifndef SEGMENTS_GENERAL_HPP
#define	SEGMENTS_GENERAL_HPP

#include "../Common/common.hpp"

#include <boost/unordered_map.hpp>
using namespace boost;

namespace segments {

    struct SegmentOptions {
        //направляющий вектор отрезка
        //единичной длины
        //направлен из первой точки отрезка ко второй
        pair<f32, f32> dirVector;

        //направляющий угол нормали к отрезку
        //единичной длины
        //направлен в такую сторону, что тройка векторов dirVector, dirVectorOrt и (dirVector x dirVectorOrt) правая
        pair<f32, f32> dirVectorOrt;
    };

    typedef pair<Point, Point> Segment;
    typedef pair<Segment, SegmentOptions> FullSegment;
    typedef unordered_map<Segment, SegmentOptions> Segments;

    class General {
    protected:
        Segments segments;

    public:

        General() {
        }
        General(const vector<Segment> &);

        virtual bool add(const Point &a, const Point &b);
        virtual bool add(const Segment &s);

        void draw(
                SDL_Surface *screen,
                Ui32 pointColor,
                Ui16 pointRadius,
                Ui32 segmentColor,
                Ui16 segmentWidth
                ) const;

        Segment beam(
                Point &currentPoint, f32 &vX, f32 &vY,
                const Point &leftTop, const Point &rightTop,
                const Point &rightDown, const Point &leftDown,
                vector<Segment> &ignore
                ) const;

    private:
        inline static bool determinantSignum(Si16 aX, Si16 aY, Si16 bX, Si16 bY);
        inline static f32 scalarMulti(f32 aX, f32 aY, f32 bX, f32 bY);
    };
}

#endif
