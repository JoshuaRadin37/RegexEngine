//
// Created by jradi on 11/4/2019.
//

#ifndef REGEXENGINE_CHARACTER_CLASS_RULE_H
#define REGEXENGINE_CHARACTER_CLASS_RULE_H


#include <evaluation/rule.h>
#include <evaluation/rules/character_class/character_class.h>
#include <evaluation/rules/character_class/fast_character_class_tester.h>

class character_class_rule : public rule{
private:
	character_class clazz;
	fast_character_class_tester tester;
	bool invert;

public:
	character_class_rule(int start_state, int end_state, const character_class &clazz,
						 bool invert);
	
	virtual bool match(char input, int *chars_consumed_ptr, int *next_state_ptr) const override;
	
	virtual std::string match_reason() const override;
};


#endif //REGEXENGINE_CHARACTER_CLASS_RULE_H
