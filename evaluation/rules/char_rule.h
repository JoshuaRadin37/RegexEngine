//
// Created by jradi on 10/30/2019.
//

#ifndef REGEXENGINE_CHAR_RULE_H
#define REGEXENGINE_CHAR_RULE_H


#include <evaluation/rule.h>

class char_rule : public rule{
private:
	char c;
public:
	char_rule(char c, int start_state, int end_state);
	
	bool match(char input, int *chars_consumed_ptr, int *next_state_ptr) const override;

protected:
	virtual std::string match_reason() const override;
};


#endif //REGEXENGINE_CHAR_RULE_H
