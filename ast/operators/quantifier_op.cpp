//
// Created by Joshua on 11/28/2019.
//

#include "quantifier_op.h"

quantifier_op::quantifier_op(std::string operator_string, const quantifier_info &info) : uniop(operator_string),
																						 info(info) {}

const quantifier_info &quantifier_op::get_info() const {
	return info;
}
