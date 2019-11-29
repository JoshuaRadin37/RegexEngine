//
// Created by Joshua on 11/28/2019.
//

#include "quantifier_info.h"

quantifier_info::quantifier_info(int min, int max, bool has_min, bool has_max, bool exactly) :
	min(min), max(max), has_max(has_max), has_min(has_min), exactly(exactly) { }

quantifier_info quantifier_info::min_q(int min) {
	return {min, 0, true, false, false};
}

quantifier_info quantifier_info::max_q(int max) {
	return {0, max, false, true, false};
}

quantifier_info quantifier_info::min_and_max_q(int min, int max) {
	return {min, max, true, true, false};
}

quantifier_info quantifier_info::none() {
	return {0, 0, false, false, false};
}

quantifier_info quantifier_info::exactly_q(int exact) {
	return {exact, 0, false, false, true};
}

std::string quantifier_info::to_string() const{
	std::string output;
	
	if(exactly) {
		output += "{";
		output += std::to_string(min);
		output += "}";
	} else {
		output += "{";
		if(has_min)
			output += std::to_string(min);
		output += ",";
		if(has_max)
			output += std::to_string(max);
		output += "}";
	}
	
	return output;
}

quantifier::quantifier(token *tok) : tok(tok), is_tok(true) {}

quantifier::quantifier(const quantifier_info &info) : info(info), is_tok(false) {}

