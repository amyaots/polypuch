#include "convex.hpp"

namespace polygon {

	inline void print(const Point &a) {
		cout << "(" << a.first << ", " << a.second << ")" << endl;
	}

	bool Convex::add(const Point &currentPoint) {
		this->pts->push_back(currentPoint);
		vector<Point> currentPoints = *(this->pts);
		this->pts->clear();
		print(currentPoint);
		for_each(currentPoints.begin(), currentPoints.end(), print);
		cout << endl;
		this->graham(currentPoints);
		
		return (find(this->pts->begin(), this->pts->end(), currentPoint) != this->pts->end());
	}
}