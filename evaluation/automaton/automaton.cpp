//
// Created by jradi on 10/30/2019.
//

#include <algorithm>
#include <map>
#include <set>
#include <utility>
#include <evaluation/rules/dismantled_rule.h>
#include "automaton.h"

automaton::automaton(ruleset *rules) : rules(rules) {}

std::vector<int> map_pairs_to_states(const std::vector<std::pair<int, int>>& v) {
	auto output = std::vector<int>();
	for (const auto &item : v) {
		output.push_back(item.first);
	}
	return output;
}

bool automaton::accept(const std::string &input) {
	std::vector<std::pair<int, int>> current_state = {std::pair<int, int>(rules->get_start_state(), 0)};
	
	auto inital_eps = rules->get_rules_for_state_and_char(rules->get_start_state(), '\0');
	for (const auto &eps_rule : inital_eps) {
		int next_state;
		int chars_moved = -1;
		if(eps_rule->match('\0', &chars_moved, &next_state) && chars_moved == 0) {
			current_state.emplace_back(std::pair<int, int>(next_state, 0));
		}
	}
	
	std::set<std::pair<int, int>> occured_states;
	
	do {
		std::set<std::pair<int, int>> next_state_set;
		for (const auto &state_and_position : current_state){
			occured_states.insert(state_and_position);
			
			
			int state = state_and_position.first;
			int position = state_and_position.second;
			
			char char_at_position = input[position];
			
			for (const auto &rule : rules->get_rules_for_state_and_char(state, char_at_position)) {
				int next_state;
				int chars_consumed;
				
				if(rule->match(char_at_position, &chars_consumed, &next_state)) {
					std::pair<int, int> next_state_position = std::pair<int, int>(next_state, position + chars_consumed);
					/*if(!rule->is_force_occur()) {
						next_state_set.insert(state_and_position);
					}*/
					if(rules->contains_accepting_state(next_state) && position + chars_consumed == input.size())
						return true;
					
					if(occured_states.find(next_state_position) == occured_states.end())
						next_state_set.insert(next_state_position);
				}
			}
		}
		
		current_state = std::vector<std::pair<int, int>>(next_state_set.begin(), next_state_set.end());
	} while(!current_state.empty() && !any_reach_end(input, current_state));
	return !current_state.empty() && rules->contains_accepting_state(map_pairs_to_states(current_state));
}

bool automaton::any_reach_end(int end, std::vector<std::pair<int, int>> state_set) {
	for (const auto &set : state_set) {
		if(set.second == end) return true;
	}
	return false;
}


automaton::automaton_state_transpose::automaton_state_transpose(int initial_state,
																std::vector<int> final_states) : initial_state(
		initial_state), final_states(std::move(final_states)) {
	
}

int automaton::find_unused_state() {
	int min_unused_state = min_created_state + 1;
	
	for (const auto &all_rule : rules->get_all_rules()) {
		if(all_rule->start_state >= min_unused_state) {
			min_unused_state = all_rule->start_state + 1;
		}
		
		if(all_rule->end_state >= min_unused_state) {
			min_unused_state = all_rule->end_state + 1;
		}
	}
	
	this->min_created_state = min_unused_state;
	return min_unused_state;
}

std::vector<int> automaton::get_used_states() const{
	std::vector<int> output;
	
	for (const auto &all_rule : rules->get_all_rules()) {
		int s1 = all_rule->start_state, s2 = all_rule->end_state;
		if(std::find(output.begin(), output.end(), s1) == output.end()) {
			output.push_back(s1);
		}
		if(std::find(output.begin(), output.end(), s2) == output.end()) {
			output.push_back(s2);
		}
	}
	
	return output;
}

int automaton::get_start_state() const {
	return rules->get_start_state();
}

std::vector<int> automaton::get_accepting_states() const {
	const std::set<int> &s = rules->get_accepting_states();
	return std::vector<int>(s.begin(), s.end());
}

automaton::automaton_state_transpose automaton::add_automaton(const automaton &other) {
	std::map<int, int> old_state_to_new_state_map;
	
	for (const int &state : other.get_used_states()) {
		int new_state = find_unused_state();
		old_state_to_new_state_map[state] = new_state;
	}
	
	for(rule* r : other.rules->get_all_rules()) {
		int start_state = old_state_to_new_state_map[r->start_state];
		int end_state = old_state_to_new_state_map[r->end_state];
		auto new_rule = r->to_dismantled_rule(start_state, end_state);
		
		rules->add_rule(new_rule);
	}
	
	int new_initial_state = old_state_to_new_state_map[other.get_start_state()];
	std::vector<int> end_states;
	for (const auto &item : other.get_accepting_states()) {
		end_states.push_back(old_state_to_new_state_map[item]);
	}
	
	
	return automaton::automaton_state_transpose(new_initial_state, end_states);
}
