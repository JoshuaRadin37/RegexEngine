//
// Created by jradi on 11/3/2019.
//

#ifndef REGEXENGINE_RULE_REQUIREMENT_H
#define REGEXENGINE_RULE_REQUIREMENT_H


#include <set>
#include <evaluation/rule.h>
#include <vector>

class rule_requirement {
private:
	bool invert = false;
	unsigned int is_epsilon = 0b11;
	std::set<int> start_states;
	std::set<int> end_states;
protected:
	rule_requirement();
	explicit rule_requirement(bool backing_field_eps);
	explicit rule_requirement(int backing_field_int, bool start);
	

public:
	static rule_requirement is_start(int s);
	static rule_requirement is_end(int e);
	static rule_requirement is_start(std::vector<int> s);
	static rule_requirement is_end(std::vector<int> e);
	static rule_requirement is_start(std::initializer_list<int> s);
	static rule_requirement is_end(std::initializer_list<int> e);
	
	static rule_requirement eps;
	
	static rule_requirement is_eps(bool e);
	
	const rule_requirement operator& (const rule_requirement& other) const;
	const rule_requirement operator! () const;
	
	bool match_requirements(rule * rule);
};


#endif //REGEXENGINE_RULE_REQUIREMENT_H
