#include "common.hpp"
#include <cmath>

namespace segments {

	SegmentsEquals::SegmentsEquals(string exceptionString) {
		this->exceptionString = exceptionString;
	}

	const char * SegmentsEquals::what() const throw () {
		return this->exceptionString.c_str();
	}

	NotSegment::NotSegment(string exceptionString) {
		this->exceptionString = exceptionString;
	}

	const char * NotSegment::what() const throw () {
		return this->exceptionString.c_str();
	}

	//решаем
	// y = Mx + N
	// y = Rx + T

	bool segmentsIntersect(const Point &a, const Point &b, const Point &c, const Point &d, Point &intersection) {
		if (a.first == b.first && a.second == b.second) {
			stringstream err;
			err << "(" << a.first << ", " << a.second << ") == ";
			err << "(" << b.first << ", " << b.second << ") ";
			err << "it is a Point!";
			throw NotSegment(err.str());
		}

		if (c.first == d.first && c.second == d.second) {
			stringstream err;
			err << "(" << c.first << ", " << c.second << ") == ";
			err << "(" << d.first << ", " << d.second << ") ";
			err << "it is a Point!";
			throw NotSegment(err.str());
		}

		if (a.first == c.first && a.second == c.second && b.first == d.first && b.second == d.second) {
			stringstream err;
			err << "(" << a.first << ", " << a.second << ") == ";
			err << "(" << c.first << ", " << c.second << ") && ";
			err << "(" << b.first << ", " << b.second << ") == ";
			err << "(" << d.first << ", " << d.second << ") ";
			err << "segments are equals!";
			throw SegmentsEquals(err.str());
		}

		//a совпадает с c
		if(a.first == c.first && a.second == c.second) {
			intersection.first = a.first;
			intersection.second = a.second;
			return true;
		}

		//a совпадает с d
		if(a.first == d.first && a.second == d.second) {
			intersection.first = a.first;
			intersection.second = a.second;
			return true;
		}

		//b совпадает с c
		if(b.first == c.first && b.second == c.second) {
			intersection.first = b.first;
			intersection.second = b.second;
			return true;
		}

		//b совпадает с d
		if(b.first == d.first && b.second == d.second) {
			intersection.first = b.first;
			intersection.second = b.second;
			return true;
		}

		//вот теперь либо система имеет единственное решение либо отрезки сонаправлены

		f32 M, N;
		f32 R, T;

		f32 Z1 = b.first - a.first;
		if (Z1) {
			M = ((f32) b.second - a.second) / Z1;
			N = ((f32) a.second * b.first - a.first * b.second) / Z1;
		} else {
			M = ((f32) b.second - a.second);
			N = ((f32) a.second * b.first - a.first * b.second);
		}

		f32 Z2 = d.first - c.first;
		if (Z2) {
			R = ((f32) d.second - c.second) / Z2;
			T = ((f32) c.second * d.first - c.first * d.second) / Z2;
		} else {
			R = ((f32) d.second - c.second);
			T = ((f32) c.second * d.first - c.first * d.second);
		}

		if ((Z1 && !Z2) || (!Z1 && Z2) || M != R) {
			//прямые пересекаются

			f32 linearX, linearY;
			
			if(Z1 && !Z2) {
				linearX = d.first;
			} else if(!Z1 && Z2) {
				linearX = b.first;
			} else {
				linearX = ((f32) T - N) / (M - R);
			}

			if(Z1 && !Z2) {
				linearY = M * linearX + N;
			} else {
				linearY = R * linearX + T;
			}

			//проверяем точку на принадлежание отрезкам a, b и c, d
			if (round((linearX - b.first) * (linearX - a.first)) > 0 || round((linearY - b.second) * (linearY - a.second)) > 0) {
				return false;
			}
			if (round((linearX - d.first) * (linearX - c.first)) > 0 || round((linearY - d.second) * (linearY - c.second)) > 0) {
				return false;
			}

			intersection.first = round(linearX);
			intersection.second = round(linearY);
			return true;
		} else {
			// прямые параллельны или совпадают
			
			if (T == N) {
				//прямые совпадают

				if ((c.first - b.first) * (c.first - a.first) > 0 || (c.second - b.second) * (c.second - a.second) > 0) {
					if ((d.first - b.first) * (d.first - a.first) > 0 || (d.second - b.second) * (d.second - a.second) > 0) {
						return false;
					} else {
						//пересечение по d
						intersection.first = d.first;
						intersection.second = d.second;
						return true;
					}
				}

				//пересечение по c
				intersection.first = c.first;
				intersection.second = c.second;
				return true;
			} else {
				//прямые параллельны
				return false;
			}
		}

		return false;
	}
}