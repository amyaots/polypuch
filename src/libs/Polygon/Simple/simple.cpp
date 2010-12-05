#include "simple.hpp"

namespace polygon {

	Simple::~Simple() {
		this->~General();
	}
}