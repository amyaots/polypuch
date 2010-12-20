#ifndef CURVE_GENERAL_HPP
#define	CURVE_GENERAL_HPP

#include "../../Polygon/General/general.hpp"
using namespace polygon;

namespace curve {

    class General {
    protected:
        vector<Point> *pts;

    public:
        General();
        General(const vector<Point> &pts);
        General(const General &obj);
        virtual ~General();

        const General& operator =(const General &obj);

        Point getStart() const;
        Point getEnd() const;
        Ui32 getSize() const;

        const bool operator ==(const General &obj) const;

        void draw(
                SDL_Surface *screen,
                Ui32 curveColor
                ) const;

        //аппроксимация кривой по некоторому принципу с использованием
        virtual void approximate(const Point &start, const Point &end);
    };
}

#endif