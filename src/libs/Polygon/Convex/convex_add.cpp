#include "convex.hpp"

#include "../../Segments/Common/common.hpp"
using namespace segments;

namespace polygon {

    //правая или левая тройка из векторов (b, a), (d, c) и ((b, a) x (d, c))
    inline bool determinantSignumComplex(const Point &a, const Point &b, const Point &c, const Point &d) {
        return (((a.first - b.first) * (c.second - d.second) - (c.first - b.first) * (a.second - d.second)) >= 0);
    }

    bool Convex::add(const Point &p) {
        
        this->pts->push_back(p);
        vector<Point> currentPoints = *(this->pts);
        this->pts->clear();
        //print(p);
        //for_each(currentPoints.begin(), currentPoints.end(), print);
        //cout << endl;
        this->graham(currentPoints);
		
        return (find(this->pts->begin(), this->pts->end(), p) != this->pts->end());

        /*
        Ui32 size = this->pts->size();
        //работаем только начиная с треугольника
        if (size < 1) {
            this->pts->push_back(p);
            return true;
        } else if (size < 3) {
            this->pts->push_back(p);
            return true;
        }

        Point leftPoint, rightPoint;

        //возьмем 3 точки которые по-любому есть
        Point firstPoint = *(this->pts->begin());
        Point secondPoint = *(this->pts->begin() + 1);
        Point thirdPoint = *(this->pts->begin() + 2);

        //возьмем 2 точки на середине двух отрезков
        Point firstSecondPoint = Point((firstPoint.first + secondPoint.first) / 2, (firstPoint.second + secondPoint.second) / 2);
        Point secondThirdPoint = Point((firstPoint.first + thirdPoint.first) / 2, (firstPoint.second + thirdPoint.second) / 2);

        //пересечем 2 медианы и получим точку внутри полигона
        Point insidePoint;
        segmentsIntersect(thirdPoint, firstSecondPoint, firstPoint, secondThirdPoint, insidePoint);

        Ui16 startPos, endPos, currentPos;
        startPos = 0;
        endPos = size;

        Point startPoint, endPoint, currentPoint;
        startPoint = *(this->pts->begin());
        endPoint = startPoint;

        //определим в каком векторе находится точка p
        while (endPos - startPos > 1) {
            currentPos = startPos + floor(((f32) endPos - startPos) / 2);
            currentPoint = this->pts->operator [](currentPos);

            if (!determinantSignum(startPoint, insidePoint, p) || !determinantSignum(p, insidePoint, currentPoint)) {
                //не в секторе (start, inside, current)
                startPoint = currentPoint;
                startPos = currentPos;
                continue;
            }

            //в секторе (start, inside, current)
            endPoint = currentPoint;
            endPos = currentPos;
        }
        Ui16 oldStartPos, oldEndPos;
        oldStartPos = startPos;
        oldEndPos = endPos;
        //точка p в секторе (start, end)
        //точки start и end находяться в секторе прикрепления

        //cout << startPoint.first << ", " << startPoint.second << endl;
        //cout << endPoint.first << ", " << endPoint.second << endl << endl;

        //определим крайнюю левую точку прикрепления (смотря из точки p на полигон)
        Point nextPoint;
        endPos = ((Ui16) (endPos + floor(((f32) size - endPos + startPos) / 2))) % size;
        while (size - endPos + startPos > 1) {
            currentPos = ((Ui16) (endPos + floor(((f32) size - endPos + startPos) / 2))) % size;
            currentPoint = this->pts->operator [](currentPos);
            nextPoint = this->pts->operator []((currentPos + 1) % size);

            if (!determinantSignumComplex(currentPoint, insidePoint, nextPoint, currentPoint)) {
                //не в секторе (start, inside, current)
                startPoint = currentPoint;
                startPos = currentPos;
                continue;
            }

            //в секторе (start, inside, current)
            endPoint = currentPoint;
            endPos = currentPos;
        }

        //определим крайнюю правую точку прикрепления (смотря из точки p на полигон)
        startPos = oldStartPos;
        endPos = oldEndPos;

        startPos = ((Ui16) (endPos + floor(((f32) size - endPos + startPos) / 2))) % size;
        while (size - endPos + startPos > 1) {
            currentPos = ((Ui16) (endPos + floor(((f32) size - endPos + startPos) / 2))) % size;
            currentPoint = this->pts->operator [](currentPos);
            nextPoint = this->pts->operator []((currentPos + 1) % size);

            if (determinantSignumComplex(currentPoint, insidePoint, nextPoint, currentPoint)) {
                //не в секторе (start, inside, current)
                startPoint = currentPoint;
                startPos = currentPos;
                continue;
            }

            //в секторе (start, inside, current)
            endPoint = currentPoint;
            endPos = currentPos;
        }

        return true;
         * */
    }
}