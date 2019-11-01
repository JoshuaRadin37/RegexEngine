//
// Created by jradi on 11/1/2019.
//

#include "dismantled_rule.h"

bool dismantled_rule::match(char input, int *chars_consumed_ptr, int *next_state_ptr) const {
	int chars_consumed;
	int next_state;
	bool output = original_rule->match(input, &chars_consumed, &next_state);
	if(!output) return output;
	*chars_consumed_ptr = chars_consumed;
	*next_state_ptr = this->get_end_state();
	return output;
}

dismantled_rule::dismantled_rule(int start_state, int end_state, bool force_occur, rule *original_rule) : rule(
		start_state, end_state, force_occur), original_rule(original_rule) {}

dismantled_rule *dismantled_rule::to_dismantled_rule(int new_start, int new_end) {
	return new dismantled_rule(new_start, new_end, is_force_occur(), original_rule);
}

std::string dismantled_rule::match_reason() const {
	return original_rule->match_reason();
}
