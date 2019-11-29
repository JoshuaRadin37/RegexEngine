//
// Created by Joshua on 11/28/2019.
//

#include "quantifier_info.h"

quantifier_info::quantifier_info(int min, int max, bool has_min, bool has_max) :
	min(min), max(max), has_max(has_max), has_min(has_min) { }

quantifier_info quantifier_info::min_q(int min) {
	return {min, 0, true, false};
}

quantifier_info quantifier_info::max_q(int max) {
	return {0, max, false, true};
}

quantifier_info quantifier_info::min_and_max_q(int min, int max) {
	return {min, max, true, true};
}

quantifier_info quantifier_info::none() {
	return {0, 0, false, false};
}

quantifier::quantifier(token *tok) : tok(tok), is_tok(true) {}

quantifier::quantifier(const quantifier_info &info) : info(info), is_tok(false) {}

