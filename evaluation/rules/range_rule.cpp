//
// Created by jradi on 11/3/2019.
//

#include "range_rule.h"

range_rule::range_rule(int start_state, int end_state, char min, char max) : rule(start_state,
																				  end_state,
																				  true),
																			 min(min), max(max) {}

bool range_rule::match(char input, int *chars_consumed_ptr, int *next_state_ptr) const {
	if(input >= min && input <= max) {
		*chars_consumed_ptr = 1;
		*next_state_ptr = get_end_state();
		return true;
	}
	
	return false;
}

std::string range_rule::match_reason() const {
	return std::string() + "in range " + min + "-" + max;
}
