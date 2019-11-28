//
// Created by jradi on 11/1/2019.
//

#include "wrapper_rule.h"

bool wrapper_rule::match(char input, int *chars_consumed_ptr, int *next_state_ptr) const {
	int chars_consumed;
	int next_state;
	bool output = original_rule->match(input, &chars_consumed, &next_state);
	if(!output) return output;
	*chars_consumed_ptr = chars_consumed;
	*next_state_ptr = this->get_end_state();
	return output;
}

wrapper_rule::wrapper_rule(int start_state, int end_state, bool force_occur, rule *original_rule) : rule(
		start_state, end_state, force_occur), original_rule(original_rule) {}

wrapper_rule *wrapper_rule::to_wrapper_rule(int new_start, int new_end) {
	return new wrapper_rule(new_start, new_end, is_force_occur(), original_rule);
}

std::string wrapper_rule::match_reason() const {
	return original_rule->match_reason();
}
