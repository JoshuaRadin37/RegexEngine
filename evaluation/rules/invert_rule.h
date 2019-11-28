//
// Created by jradi on 11/3/2019.
//

#ifndef REGEXENGINE_INVERT_RULE_H
#define REGEXENGINE_INVERT_RULE_H


#include <evaluation/rule.h>
#include "range_rule.h"
#include "char_rule.h"

template <class T>
class invert_rule : public rule {
protected:
	T* my_rule;

public:
	invert_rule(int start_state, int end_state, T *original_rule) : rule(start_state, end_state, true), my_rule(original_rule) { }
	
	virtual bool match(char input, int *chars_consumed_ptr, int *next_state_ptr) const = 0;
};


#endif //REGEXENGINE_INVERT_RULE_H
