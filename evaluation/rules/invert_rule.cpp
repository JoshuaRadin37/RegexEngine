//
// Created by jradi on 11/3/2019.
//

#include "invert_rule.h"




invert_rule::invert_rule(int start_state, int end_state, range_rule *original_rule) : rule(start_state,
																							  end_state,
																							  true),
																					  my_rule(original_rule) {}

bool invert_rule::match(char input, int *chars_consumed_ptr, int *next_state_ptr) const {
	if(input <= my_rule->min && input > my_rule->max) {
		*chars_consumed_ptr = 1;
		*next_state_ptr = get_end_state();
		return true;
	}
	
	return false;
}