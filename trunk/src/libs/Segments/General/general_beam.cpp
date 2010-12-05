#include "general.hpp"
#include "../../SDL/Line/line.hpp"
#include "../../SDL/Circle/circle.hpp"
using namespace sdl;

#include <cmath>

namespace segments {

	inline void print(const pair<f32, f32> &a) {
		cout << "(" << a.first << ", " << a.second << ")" << endl;
	}

	//обычное скалярное произведение

	f32 General::scalarMulti(f32 aX, f32 aY, f32 bX, f32 bY) {
		return (aX * bX + aY * bY);
	}

	//лучик из точки currentPoint и направляющим единичным вектором (vX, xY)
	//прямоугольник leftTop, rightTop, leftDown, rightDown ограничивает лучик
	//этот метод реализует одно отражение
	//изменения сохраняются прямо в currentPoint, vX, vY
	//метод выплевывает текущий прямолинейный отрезок движения луча

	Segment General::beam(
			Point &currentPoint, f32 &vX, f32 &vY,
			const Point &leftTop, const Point &rightTop,
			const Point &rightDown, const Point &leftDown,
			vector<Segment> &ignore
			) const {

		vector<Segment> newIgnore;

		vector<Segment>::iterator vt;
		//cout << "ignore list" << endl;
		/*
		for(vt = ignore.begin(); vt != ignore.end(); vt++) {
			print((*vt).first);
			print((*vt).second);
		}
		cout << endl;
		*/
		
		Pi width = rightTop.first - leftTop.first;
		Pi height = leftDown.second - leftTop.second;

		//нельзя чтобы координаты конечной точки стали меньше нуля
		//выбираем эту точку так чтобы отрезок (currentPoint, endPoint) полюбому пересекал прямоугольник
		Point endPoint;
		if (!vX) {
			endPoint.first = currentPoint.first;
			Si16 endPointSecond = currentPoint.second + vY * height;
			if (endPointSecond < 0) {
				endPoint.second = 0;
			} else {
				endPoint.second = endPointSecond;
			}
		} else if (!vY) {
			endPoint.second = currentPoint.second;
			Si16 endPointFirst = currentPoint.first + vX * width;
			if (endPointFirst < 0) {
				endPoint.first = 0;
			} else {
				endPoint.first = endPointFirst;
			}
		} else {
			if (vX < 0 && vY < 0) {
				f32 countX = currentPoint.first / (-vX);
				f32 countY = currentPoint.second / (-vY);
				if (countX >= countY) {
					endPoint.second = 0;
					endPoint.first = currentPoint.first + vX * countY;
				} else {
					endPoint.first = 0;
					endPoint.second = currentPoint.second + vY * countX;
				}
			} else if (vX >= 0 && vY < 0) {
				f32 countX = width / vX;
				f32 countY = currentPoint.second / (-vY);
				if (countX >= countY) {
					endPoint.second = 0;
					endPoint.first = currentPoint.first + vX * countY;
				} else {
					endPoint.first = currentPoint.first + width;
					endPoint.second = currentPoint.second + vY * countX;
				}
			} else if (vX < 0 && vY >= 0) {
				f32 countX = currentPoint.first / (-vX);
				f32 countY = height / vY;
				if (countX >= countY) {
					endPoint.first = currentPoint.first + vX * countY;
					endPoint.second = currentPoint.second + height;
				} else {
					endPoint.first = 0;
					endPoint.second = currentPoint.second + vY * countX;
				}
			} else {
				endPoint.first = currentPoint.first + width;
				endPoint.second = currentPoint.second + ((f32) width / vX) * vY;
			}
		}

		//пересекаем со сторонами
		Point intersection;
		SegmentOptions currentSegmentOptions;

		//print(currentPoint);
		//print(endPoint);
		//print(leftTop);
		//print(rightTop);
		//cout << (segmentsIntersect(leftTop, rightTop, currentPoint, endPoint, intersection)) << endl << endl;
		if (
				find(ignore.begin(), ignore.end(), Segment(leftTop, rightTop)) == ignore.end() &&
				segmentsIntersect(leftTop, rightTop, currentPoint, endPoint, intersection)
				) {
			currentSegmentOptions.dirVector.first = 1;
			currentSegmentOptions.dirVector.second = 0;
			currentSegmentOptions.dirVectorOrt.first = 0;
			currentSegmentOptions.dirVectorOrt.second = -1;
			if(intersection != endPoint) {
				newIgnore.clear();
				newIgnore.push_back(Segment(leftTop, rightTop));
			} else {
				newIgnore.push_back(Segment(leftTop, rightTop));
			}
			endPoint = intersection;
		}

		//print(currentPoint);
		//print(endPoint);
		//print(rightTop);
		//print(rightDown);
		//cout << (segmentsIntersect(rightTop, rightDown, currentPoint, endPoint, intersection)) << endl << endl;
		if (
				find(ignore.begin(), ignore.end(), Segment(rightTop, rightDown)) == ignore.end() &&
				segmentsIntersect(rightTop, rightDown, currentPoint, endPoint, intersection)
				) {
			currentSegmentOptions.dirVector.first = 0;
			currentSegmentOptions.dirVector.second = 1;
			currentSegmentOptions.dirVectorOrt.first = 1;
			currentSegmentOptions.dirVectorOrt.second = 0;
			if(intersection != endPoint) {
				newIgnore.clear();
				newIgnore.push_back(Segment(rightTop, rightDown));
			} else {
				newIgnore.push_back(Segment(rightTop, rightDown));
			}
			endPoint = intersection;
		}

		//print(currentPoint);
		//print(endPoint);
		//print(rightDown);
		//print(leftDown);
		//cout << (segmentsIntersect(rightDown, leftDown, currentPoint, endPoint, intersection)) << endl << endl;
		if (
				find(ignore.begin(), ignore.end(), Segment(rightDown, leftDown)) == ignore.end() &&
				segmentsIntersect(rightDown, leftDown, currentPoint, endPoint, intersection)
				) {
			currentSegmentOptions.dirVector.first = -1;
			currentSegmentOptions.dirVector.second = 0;
			currentSegmentOptions.dirVectorOrt.first = 0;
			currentSegmentOptions.dirVectorOrt.second = 1;
			if(intersection != endPoint) {
				newIgnore.clear();
				newIgnore.push_back(Segment(rightDown, leftDown));
			} else {
				newIgnore.push_back(Segment(rightDown, leftDown));
			}
			endPoint = intersection;
		}

		//print(currentPoint);
		//print(endPoint);
		//print(leftDown);
		//print(leftTop);
		//cout << (segmentsIntersect(leftDown, leftTop, currentPoint, endPoint, intersection)) << endl << endl;
		if (
				find(ignore.begin(), ignore.end(), Segment(leftDown, leftTop)) == ignore.end() &&
				segmentsIntersect(leftDown, leftTop, currentPoint, endPoint, intersection)
				) {
			currentSegmentOptions.dirVector.first = 0;
			currentSegmentOptions.dirVector.second = -1;
			currentSegmentOptions.dirVectorOrt.first = -1;
			currentSegmentOptions.dirVectorOrt.second = 0;
			if(intersection != endPoint) {
				newIgnore.clear();
				newIgnore.push_back(Segment(leftDown, leftTop));
			} else {
				newIgnore.push_back(Segment(leftDown, leftTop));
			}
			endPoint = intersection;
		}

		//print(endPoint);
		//cout << endl;

		//пересекаем текущий отрезок со всеми отрезками
		//в результате endPoint становится в ту точку, в которую попал бы луч
		//исходя из точки currentPoint по напрвлению (vX, vY)
		//сохраняем опции того самого сегмента, от которого луч собрался отражаться
		Segments::const_iterator it;
		Segment currentSegment;

		for (it = this->segments.begin(); it != this->segments.end(); it++) {
			currentSegment = (*it).first;
			try {
				if (
						find(ignore.begin(), ignore.end(), Segment(currentSegment.first, currentSegment.second)) == ignore.end() &&
						segmentsIntersect(currentSegment.first, currentSegment.second, currentPoint, endPoint, intersection)
						) {
					currentSegmentOptions = (*it).second;
					
					if(intersection != endPoint) {
						newIgnore.clear();
						newIgnore.push_back(Segment(currentSegment.first, currentSegment.second));
					} else {
						newIgnore.push_back(Segment(currentSegment.first, currentSegment.second));
					}
					endPoint = intersection;
				}
			} catch (NotSegment &ns) {
				cerr << ns.what() << endl;
			} catch (SegmentsEquals &se) {
				cerr << se.what() << endl;
			}
		}

		Segment old(currentPoint, endPoint);
		//print(currentPoint);
		//print(endPoint);
		//cout << vX << " " << vY << endl;
		//print(currentSegmentOptions.dirVector);
		//print(currentSegmentOptions.dirVectorOrt);
		//cout << endl;

		//отражаем наш лучик
		//вспоминаем что скалярное произведение a * b - величина проекции a на b
		//найдем проекции на ортонормированную систему текущего сегмента dirVector, dirVectorOrt
		//поменяем направление проеции на dirVectorOrt
		//сложим проекции обратно - получим отраженный луч!
		f32 scalarDirVector = scalarMulti(currentSegmentOptions.dirVector.first, currentSegmentOptions.dirVector.second, vX, vY);
		f32 scalarDirVectorOrt = scalarMulti(currentSegmentOptions.dirVectorOrt.first, currentSegmentOptions.dirVectorOrt.second, vX, vY);

		vX = currentSegmentOptions.dirVector.first * scalarDirVector - currentSegmentOptions.dirVectorOrt.first * scalarDirVectorOrt;
		vY = currentSegmentOptions.dirVector.second * scalarDirVector - currentSegmentOptions.dirVectorOrt.second * scalarDirVectorOrt;

		//cout << vX << " " << vY << endl << endl;

		currentPoint = endPoint;
		ignore = newIgnore;
		return old;
	}
}