//
// Created by jradi on 11/4/2019.
//

#include "character_class_rule.h"

character_class_rule::character_class_rule(int start_state, int end_state, const character_class &clazz,
										   bool invert) : rule(start_state, end_state,true),
														  clazz(clazz),
														  invert(invert),
														  tester(fast_character_class_tester(clazz)) {
	tester.construct();
}

bool character_class_rule::match(char input, int *chars_consumed_ptr, int *next_state_ptr) const {
	if(!tester.is_constructed()) {
		return false;
	}
	
	bool output = !invert == tester.check(input);
	if(output) {
		*chars_consumed_ptr = 1;
		*next_state_ptr = get_end_state();
	}
	return output;
}
