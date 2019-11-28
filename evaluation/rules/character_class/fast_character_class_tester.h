//
// Created by jradi on 11/4/2019.
//

#ifndef REGEXENGINE_FAST_CHARACTER_CLASS_TESTER_H
#define REGEXENGINE_FAST_CHARACTER_CLASS_TESTER_H


#include "character_class.h"

class fast_character_class_tester {
private:
	character_class c_class;
	std::vector<bool>* checks;
	
	int subtraction = 0;
	char min_char = 0;
	char max_char = 0;
	
	bool constructed = false;
public:
	explicit fast_character_class_tester(const character_class &c_class);
	
	virtual ~fast_character_class_tester();
	
	void construct();
	bool check(char c) const;
	
	bool is_constructed() const;
};


#endif //REGEXENGINE_FAST_CHARACTER_CLASS_TESTER_H
