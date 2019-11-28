//
// Created by jradi on 11/5/2019.
//

#ifndef REGEXENGINE_INVERT_CHARACTER_CLASS_H
#define REGEXENGINE_INVERT_CHARACTER_CLASS_H


#include <evaluation/rules/character_class_rule.h>
#include "evaluation/rules/invert_rule.h"

class invert_character_class : public invert_rule<character_class_rule> {
public:
	invert_character_class(int start_state, int end_state, character_class_rule *original_rule);

public:
	virtual bool match(char input, int *chars_consumed_ptr, int *next_state_ptr) const override;
};


#endif //REGEXENGINE_INVERT_CHARACTER_CLASS_H
