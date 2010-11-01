#include "segment.hpp"

namespace polygon {

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
	// A B * t = E
	// C D   s   F

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

		//вот теперь либо система имеет единственное решение либо отрезки сонаправлены

		Si16 A = b.first - a.first;
		Si16 C = b.second - a.second;
		Si16 B = c.first - d.first;
		Si16 D = c.second - d.second;

		Si16 E = c.first - a.first;
		Si16 F = c.second - a.second;

		cout << "A = " << A << " B = " << B << "   E = " << E << endl;
		cout << "C = " << C << " D = " << D << "   F = " << F << endl;

		Si16 determinant = D * A - B * C;

		f32 s, t;

		if (determinant) {
			//единственное решение

			s = ((f32) (F * A - C * E)) / determinant;
			t = ((f32) E - B * s) / A;

			if (s < 0 || s > 1 || t < 0 || t > 1) {
				return false;
			}

			intersection.first = c.first + s * (d.first - c.first);
			intersection.second = c.second + s * (d.second - c.second);
			return true;
		} else {
			//отрезки сонаправлены

			if (!A) {
				//оба отрезка вертикальные

				if (!E) {
					//они лежат на одной вертикальной прямой

					s = ((f32) F) / C;
					if (s >= 0 && s <= 1) {
						intersection.first = b.first;
						intersection.second = b.second;
						return true;
					}
					s = ((f32) F - D) / C;
					if (s >= 0 && s <= 1) {
						intersection.first = a.first;
						intersection.second = a.second;
						return true;
					}
					return false;
				} else {
					//они лежат на параллельных прямых
					return false;
				}
			} else if (!C) {
				//оба отрезка горизонтальные

				if (!F) {
					//они лежат на одной горизонтальной прямой

					s = ((f32) E) / A;
					if (s >= 0 && s <= 1) {
						intersection.first = b.first;
						intersection.second = b.second;
						return true;
					}
					s = ((f32) E - B) / A;
					if (s >= 0 && s <= 1) {
						intersection.first = a.first;
						intersection.second = a.second;
						return true;
					}
					return false;
				} else {
					//они лежат на параллельных горизонтальных прямых
					return false;
				}
			} else {
				if (A * F == B * E) {
					//они лежат на одной прямой (не вертикальной и не горизонтальной)

					s = ((f32) E) / A;
					if (s >= 0 && s <= 1) {
						intersection.first = b.first;
						intersection.second = b.second;
						return true;
					}
					s = ((f32) E - B) / A;
					if (s >= 0 && s <= 1) {
						intersection.first = a.first;
						intersection.second = a.second;
						return true;
					}
					return false;
				} else {
					//они лежат на параллельных прямых (не вертикальных и не горизонтальных)
					return false;
				}
			}
		}
	}
}