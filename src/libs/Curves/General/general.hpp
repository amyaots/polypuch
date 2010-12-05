#ifndef CURVES_GENERAL_HPP
#define	CURVES_GENERAL_HPP

#include "../../Curve/General/general.hpp"

#include "../../Polygon/General/general.hpp"
using namespace polygon;

namespace curves {

    typedef curve::General Curve;

    class General {
    protected:
        vector<curve::General> *curves;

    public:
        General();
        General(const vector<curve::General> &pts);
        General(const General &obj);
        virtual ~General();

        virtual Ui32 getSize() const;

        virtual bool add(const Curve &p);
        virtual void insert(const Curve &p, Pi index);

        const General & operator =(const General &obj);
        const General operator +(const General &obj) const;

        void draw(
                SDL_Surface *screen,
                Ui32 pointColor,
                Ui16 pointRadius,
                Ui32 curveColor
                ) const;
    };
}

#endif