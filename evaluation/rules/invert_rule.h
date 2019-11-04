//
// Created by jradi on 11/3/2019.
//

#ifndef REGEXENGINE_INVERT_RULE_H
#define REGEXENGINE_INVERT_RULE_H


#include <evaluation/rule.h>
#include "range_rule.h"

class invert_rule : public rule {
private:
	range_rule* my_rule;

public:
	invert_rule(int start_state, int end_state, range_rule *original_rule);
	
	 bool match(char input, int *chars_consumed_ptr, int *next_state_ptr) const override;
};


#endif //REGEXENGINE_INVERT_RULE_H
