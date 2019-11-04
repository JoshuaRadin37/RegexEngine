//
// Created by jradi on 11/4/2019.
//

#include "fast_character_class_tester.h"
#include <climits>

fast_character_class_tester::fast_character_class_tester(const character_class &c_class) : c_class(c_class) {}

fast_character_class_tester::~fast_character_class_tester() {
	delete [] checks;
}

void fast_character_class_tester::construct() {
	char min = CHAR_MAX, max = CHAR_MIN;
	
	for (const auto &c : c_class) {
		if(c < min) {
			min = c;
		}
		if (c > max) {
			max = c;
		}
	}
	
	subtraction = -min;
	if(min > max) return;
	unsigned int size = max - min + 1;
	checks = new bool[size];
	for (unsigned int i = 0; i < size; ++i) {
		checks[i] = false;
	}
	
	for (const auto &c : c_class) {
		int modified = ((int) c) - subtraction;
		checks[modified] = true;
	}
	
	constructed = true;
}

bool fast_character_class_tester::check(char c) const{
	if(!constructed) return false;
	int modified = ((int) c) - subtraction;
	return checks[modified];
}

bool fast_character_class_tester::is_constructed() const {
	return constructed;
}
