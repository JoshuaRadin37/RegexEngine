//
// Created by jradi on 10/30/2019.
//

#ifndef REGEXENGINE_RULESET_H
#define REGEXENGINE_RULESET_H


#include <unordered_map>
#include <vector>
#include <evaluation/rule.h>
#include <set>
#include "rule_requirement.h"


class automaton;

class ruleset {

private:
	std::unordered_map<int, std::vector<rule *>> *state_to_rule_map;
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
	
	bool contains_state(int state);
	
	int get_start_state() const;
	
	void set_start_state(int new_start_state);
	
	void add_accepting_state(int s);
	void add_accepting_state(const std::vector<int>& s);
	
	bool contains_accepting_state(const std::vector<int> &states);
	
	bool contains_accepting_state(int state);
	
	std::set<int> get_accepting_states() const;
	
	
	
	
	std::vector<rule *> get_all_rules() const;
	
	std::set<int> epsilon_closure(int state) const;
	
	std::vector<rule *> get_rules_that(rule_requirement r) const;
	inline std::vector<rule *> get_epsilon_rules() const {
		return get_rules_that(rule_requirement::is_eps(true));
	}
	inline std::vector<rule *> get_epsilon_rules(int start_state) const {
		return get_rules_that(rule_requirement::is_eps(true) & rule_requirement::is_start(start_state));
	}
	
	void remove_useless_rules();
	void remove_useless_accepting_states();
	
	friend class automaton;
	
	std::vector<rule *> operator<<(const rule_requirement& r);
	
};
#endif //REGEXENGINE&_RULESET_H
