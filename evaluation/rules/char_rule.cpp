//
// Created by jradi on 10/30/2019.
//

#include "char_rule.h"

char_rule::char_rule(char c, int start_state, int end_state) : rule(start_state, end_state, true), c(c) { }

bool char_rule::match(char input, int *chars_consumed_ptr, int *next_state_ptr) const {
	if(input == c) {
		*chars_consumed_ptr = 1;
		*next_state_ptr = get_end_state();
		return true;
	}
	
	return false;
}

std::string char_rule::match_reason() const {
	return std::string() + c;
}
