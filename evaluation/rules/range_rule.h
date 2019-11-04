//
// Created by jradi on 11/3/2019.
//

#ifndef REGEXENGINE_RANGE_RULE_H
#define REGEXENGINE_RANGE_RULE_H


#include <evaluation/rule.h>

class range_rule : public rule {
private:
	friend class invert_rule;
	char min;
	char max;
public:
	range_rule(int start_state, int end_state, char min, char max);
	
	virtual bool match(char input, int *chars_consumed_ptr, int *next_state_ptr) const override;
	
	virtual std::string match_reason() const override;
};


#endif //REGEXENGINE_RANGE_RULE_H
