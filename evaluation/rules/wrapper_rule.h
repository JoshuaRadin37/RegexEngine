//
// Created by jradi on 11/1/2019.
//

#ifndef REGEXENGINE_WRAPPER_RULE_H
#define REGEXENGINE_WRAPPER_RULE_H


#include <evaluation/rule.h>

class wrapper_rule : public rule{
private:
	rule* original_rule;
public:
	wrapper_rule(int start_state, int end_state, bool force_occur, rule *original_rule);
	
	virtual bool match(char input, int *chars_consumed_ptr, int *next_state_ptr) const override;
	
	virtual wrapper_rule *to_wrapper_rule(int new_start, int new_end) override;
	
	std::string match_reason() const override;
};


#endif //REGEXENGINE_WRAPPER_RULE_H
