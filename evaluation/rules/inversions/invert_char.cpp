//
// Created by jradi on 11/5/2019.
//

#include "invert_char.h"

bool invert_char::match(char input, int *chars_consumed_ptr, int *next_state_ptr) const {
	if(input != my_rule->get_c()) {
		*chars_consumed_ptr = 1;
		*next_state_ptr = get_end_state();
		return true;
	}
	
	return false;
}
