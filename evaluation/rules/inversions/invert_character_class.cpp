//
// Created by jradi on 11/5/2019.
//

#include "invert_character_class.h"

bool invert_character_class::match(char input, int *chars_consumed_ptr, int *next_state_ptr) const {

}

invert_character_class::invert_character_class(int start_state, int end_state, character_class_rule *original_rule)
		: invert_rule(start_state, end_state, original_rule) {}
