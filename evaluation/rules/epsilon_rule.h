//
// Created by jradi on 10/30/2019.
//

#ifndef REGEXENGINE_EPSILON_RULE_H
#define REGEXENGINE_EPSILON_RULE_H


#include <evaluation/rule.h>

class epsilon_rule : public rule {
public:
	epsilon_rule(int start_state, int end_state);
	
	bool match(char input, int *chars_consumed_ptr, int *next_state_ptr) const override;
};


#endif //REGEXENGINE_EPSILON_RULE_H
