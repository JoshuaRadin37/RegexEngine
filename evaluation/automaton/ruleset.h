//
// Created by jradi on 10/30/2019.
//

#ifndef REGEXENGINE_RULESET_H
#define REGEXENGINE_RULESET_H


#include <map>
#include <vector>
#include <evaluation/rule.h>
#include <set>

class ruleset {

private:
	std::multimap<int, rule *> *state_to_rule_map;
	int start_state = 0;
	std::set<int> accepting_states;

public:
	ruleset();
	ruleset(int start, std::initializer_list<int> accepting_states);
	
	virtual ~ruleset();
	
	void add_rule(rule *new_rule);
	void add_rule(int start, char c, int end);
	void add_epsilon_rule(int start, int end);
	
	std::vector<rule *> get_rules_for_state(int state);
	std::vector<rule *> get_rules_for_state_and_char(int state, char c);
	
	int get_start_state() const;
	
	void set_start_state(int new_start_state);
	
	void add_accepting_state(int s);
	
	bool contains_accepting_state(const std::vector<int>& states);
};


#endif //REGEXENGINE&_RULESET_H
