//
// Created by jradi on 10/30/2019.
//

#include "epsilon_rule.h"

epsilon_rule::epsilon_rule(int start_state, int end_state) : rule(start_state, end_state,
																  false) {}

bool epsilon_rule::match(char input, int *chars_consumed_ptr, int *next_state_ptr) const {
	*chars_consumed_ptr = 0;
	*next_state_ptr = get_end_state();
	return true;
}

std::string epsilon_rule::match_reason() const {
	return "epsilon";
}

