//
// Created by jradi on 10/30/2019.
//

#include <evaluation/rules/char_rule.h>
#include <evaluation/rules/epsilon_rule.h>
#include "ruleset.h"

ruleset::~ruleset() {
	delete(state_to_rule_map);
}

ruleset::ruleset() {
	state_to_rule_map = new std::multimap<int, rule *>();
}

ruleset::ruleset(int start, std::initializer_list<int> accepting_states) {
	start_state = start;
	this->accepting_states = accepting_states;
}

void ruleset::add_rule(rule *new_rule) {
	auto val = std::pair<int, rule *>(new_rule->get_start_state(), new_rule);
	state_to_rule_map->insert(val);
}

std::vector<rule *> ruleset::get_rules_for_state(int state) {
	
	auto result = (*state_to_rule_map).equal_range(state);
	std::vector<rule *> output = std::vector<rule *>();
	for(auto member = result.first; member != result.second; member.operator++()) {
		output.push_back(member.operator*().second);
	}
	return output;
}

std::vector<rule *> ruleset::get_rules_for_state_and_char(int state, char c) {
	auto initial = get_rules_for_state(state);
	std::vector<rule *> output;
	for (const auto &item : initial) {
		int next_state, chars_consumed;
		if(item->match(c, &chars_consumed ,&next_state)) {
			output.emplace_back(item);
		}
	}
	return output;
}

int ruleset::get_start_state() const {
	return start_state;
}

void ruleset::set_start_state(int new_start_state) {
	ruleset::start_state = new_start_state;
}

void ruleset::add_accepting_state(int s) {
	if(accepting_states.find(s) != accepting_states.end()) return;
	accepting_states.insert(s);
}

bool ruleset::contains_accepting_state(const std::vector<int>& states) {
	for (const auto &item : states) {
		if(accepting_states.find(item) != accepting_states.end()) return true;
	}
	
	return false;
}

void ruleset::add_rule(int start, char c, int end) {
	rule * created = new char_rule(c, start, end);
	add_rule(created);
}

void ruleset::add_epsilon_rule(int start, int end) {
	add_rule(new epsilon_rule(start, end));
}
