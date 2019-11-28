//
// Created by jradi on 10/30/2019.
//

#include <evaluation/rules/char_rule.h>
#include <evaluation/rules/epsilon_rule.h>
#include <queue>
#include "ruleset.h"

ruleset::~ruleset() {
	delete(state_to_rule_map);
}

ruleset::ruleset() {
	state_to_rule_map = new std::unordered_map<int, std::vector<rule *>>();
}

ruleset::ruleset(int start, std::initializer_list<int> accepting_states) : ruleset() {
	start_state = start;
	this->accepting_states = accepting_states;
	
}

bool ruleset::contains_state(int state) {
	return state_to_rule_map->find(state) != state_to_rule_map->end();
}

void ruleset::add_rule(rule *new_rule) {
	int state = new_rule->get_start_state();
	
	if(!contains_state(state)) {
		(*state_to_rule_map)[state] = std::vector<rule *>();
	}
	(*state_to_rule_map)[state].push_back(new_rule);
}

std::vector<rule *> ruleset::get_rules_for_state(int state) {
	return (*state_to_rule_map)[state];
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

void ruleset::add_accepting_state(const std::vector<int> &s) {
	accepting_states.insert(s.begin(), s.end());
}


std::set<int> ruleset::get_accepting_states() const {
	return accepting_states;
}

bool ruleset::contains_accepting_state(int state) {
	return accepting_states.find(state) != accepting_states.end();
}

void ruleset::add_rule(int start, char c, int end) {
	rule * created = new char_rule(c, start, end);
	add_rule(created);
}

void ruleset::add_epsilon_rule(int start, int end) {
	add_rule(new epsilon_rule(start, end));
}

std::vector<rule *> ruleset::get_all_rules() const{
	auto output = std::vector<rule *>();
	for (const auto &item : *state_to_rule_map) {
		std::vector<rule *> rule_vector = item.second;
		for (rule * r : rule_vector) {
			output.push_back(r);
		}
	}
	return output;
}

std::vector<rule *> ruleset::get_rules_that(rule_requirement r) const{
	std::vector<rule *> output;
	for (const auto &all_rule : get_all_rules()) {
		if(r.match_requirements(all_rule)) {
			output.push_back(all_rule);
		}
	}
	return output;
}

std::vector<rule *> ruleset::operator<<(const rule_requirement& r) {
	return get_rules_that(r);
}

std::set<int> ruleset::epsilon_closure(int state) const {
	std::set<int> visited;
	
	std::queue<int> queue;
	queue.push(state);
	
	do {
	
		int current = queue.front();
		queue.pop();
		visited.insert(current);
		
		std::vector<rule *> eps_rules = get_epsilon_rules(current);
		
		for (const auto &eps_rule : eps_rules) {
			int next_state = eps_rule->get_end_state();
			
			if (visited.find(next_state) == visited.end()) {
				queue.push(next_state);
			}
		}
		
		
	} while (!queue.empty());
	
	
	
	
	return visited;
}
