#ifndef GENERAL_HPP
#define	GENERAL_HPP

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include "../../SDL/Common/common.hpp"
using namespace sdl;

namespace polygon {

    typedef Ui16 Pi;
    #define Pi_Min Ui16_Min
    #define Pi_Max Ui16_Max

    typedef std::pair<Pi, Pi> Point;

    class General {
    protected:
        vector<Point> *pts;

    public:
        General();
        General(const vector<Point> &pts);
        General(const General &obj);
        ~General();

        virtual Ui32 getSize() const;

        virtual bool add(const Point &p);
        virtual void insert(const Point &p, Pi index);

        const General & operator =(const General &obj);
        const General operator +(const General &obj) const;

        void draw(
            SDL_Surface *screen,
            Ui32 pointColor,
            Ui16 pointRadius,
            Ui32 segmentColor,
            Ui16 segmentWidth,
            bool drawLines
        ) const;

        friend ostream & operator <<(ostream &os, const General &obj);
    };
}

#endif
