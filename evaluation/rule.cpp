//
// Created by jradi on 10/30/2019.
//

#include "rule.h"
#include "rules/dismantled_rule.h"

int rule::get_start_state() const {
	return start_state;
}

int rule::get_end_state() const {
	return end_state;
}

bool rule::is_force_occur() const {
	return force_occur;
}

rule::rule(int start_state, int end_state, bool force_occur) : start_state(start_state), end_state(end_state),
															   force_occur(force_occur) {}

dismantled_rule *rule::to_dismantled_rule(int new_start, int new_end) {
	return new dismantled_rule(new_start, new_end, force_occur, this);
}


