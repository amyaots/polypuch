#include "simple.hpp"
#include "../../Segments/Common/common.hpp"
using namespace segments;

namespace polygon {

	Simple::Simple(const vector<Point> &pts) {
		this->pts = new vector<Point > ();
		vector<Point>::const_iterator it;
		for (it = pts.begin(); it != pts.end(); it++) {
			vector<Point>::iterator findit;
			findit = find(this->pts->begin(), this->pts->end(), *it);
			if (findit == this->pts->end()) {
				this->add(*it);
			}
		}
	}

	bool Simple::add(const Point &A) {
		if(this->pts->size() < 3) {
			this->pts->push_back(A);
			return true;
		}

		//нельзя чтобы совпадало с какой-нибудь точкой
		vector<Point>::iterator findit;
		findit = find(this->pts->begin(), this->pts->end(), A);
		if(findit != this->pts->end()) {
			cout << "совпало!" << endl;
			return false;
		}

		vector<Point>::iterator it, jt;
		Point B, C, D, E, intersection;

		Pi currentIndex;
		C.first = (*(this->pts->begin() + this->pts->size() - 1)).first;
		C.second = (*(this->pts->begin() + this->pts->size() - 1)).second;
		for(it = this->pts->begin(), currentIndex = 0; it != this->pts->end(); it++, currentIndex++) {
			B.first = C.first;
			B.second = C.second;
			
			C.first = (*it).first;
			C.second = (*it).second;

			/*
			cout << "положим" << endl;
			cout << "(" << B.first << ", " << B.second << ") ";
			cout << "(" << C.first << ", " << C.second << ")" << endl << endl;
			 * */

			bool addAtCurrentIndex = true;
			E.first = (*(this->pts->begin() + this->pts->size() - 1)).first;
			E.second = (*(this->pts->begin() + this->pts->size() - 1)).second;
			for(jt = this->pts->begin(); jt != this->pts->end(); jt++) {
				D.first = E.first;
				D.second = E.second;

				E.first = (*jt).first;
				E.second = (*jt).second;

				try{
					if(segmentsIntersect(A, B, D, E, intersection)) {
						/*
						cout << "(" << A.first << ", " << A.second << ") ";
						cout << "(" << B.first << ", " << B.second << ")" << endl;
						cout << "(" << D.first << ", " << D.second << ") ";
						cout << "(" << E.first << ", " << E.second << ")" << endl;
						cout << "пересечение!" << endl;
						cout << "(" << intersection.first << ", " << intersection.second << ")"<< endl << endl;
						* */
						if(intersection.first != B.first || intersection.second != B.second) {
							//cout << "но они НЕ пересекаются по ";
							//cout << "(" << B.first << ", " << B.second << ")" << endl << endl;
							addAtCurrentIndex = false;
							break;
						} else {
							//cout << "но они пересекаются по ";
							//cout << "(" << B.first << ", " << B.second << ")" << endl << endl;
						}
					} else {
						/*
						cout << "(" << A.first << ", " << A.second << ") ";
						cout << "(" << B.first << ", " << B.second << ")" << endl;
						cout << "(" << D.first << ", " << D.second << ") ";
						cout << "(" << E.first << ", " << E.second << ")" << endl;
						cout << "нет пересечения!" << endl << endl;
						 * */
					}
					if(segmentsIntersect(A, C, D, E, intersection)) {
						/*
						cout << "(" << A.first << ", " << A.second << ") ";
						cout << "(" << C.first << ", " << C.second << ")" << endl;
						cout << "(" << D.first << ", " << D.second << ") ";
						cout << "(" << E.first << ", " << E.second << ")" << endl;
						cout << "пересечение!" << endl;
						cout << "(" << intersection.first << ", " << intersection.second << ")"<< endl << endl;
						* */
						if(intersection.first != C.first || intersection.second != C.second) {
							//cout << "но они НЕ пересекаются по ";
							//cout << "(" << C.first << ", " << C.second << ")" << endl << endl;
							addAtCurrentIndex = false;
							break;
						} else {
							//cout << "но они пересекаются по ";
							//cout << "(" << C.first << ", " << C.second << ")" << endl << endl;
						}
					} else {
						/*
						cout << "(" << A.first << ", " << A.second << ") ";
						cout << "(" << C.first << ", " << C.second << ")" << endl;
						cout << "(" << D.first << ", " << D.second << ") ";
						cout << "(" << E.first << ", " << E.second << ")" << endl;
						cout << "нет пересечения!" << endl << endl;
						 * */
					}
				} catch(SegmentsEquals &se) {
					cerr << se.what() << endl;
					return false;
				} catch(NotSegment &ns) {
					cerr << ns.what() << endl;
					return false;
				}
			}

			if(addAtCurrentIndex) {
				//cout << "добавляем!!" << endl << endl;
				this->pts->insert(this->pts->begin() + currentIndex, A);
				return true;
			} else {
				//cout << "не добавляем" << endl;
			}
		}
		
		return false;
	}
}