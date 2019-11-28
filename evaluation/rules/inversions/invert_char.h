//
// Created by jradi on 11/5/2019.
//

#ifndef REGEXENGINE_INVERT_CHAR_H
#define REGEXENGINE_INVERT_CHAR_H
#include "evaluation/rules/invert_rule.h"

class invert_char : public invert_rule<char_rule> {
public:
	bool match(char input, int *chars_consumed_ptr, int *next_state_ptr) const override;
};



#endif //REGEXENGINE_INVERT_CHAR_H
