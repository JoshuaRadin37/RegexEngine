//
// Created by jradi on 10/30/2019.
//

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
	
	do {
		std::vector<std::pair<int, int>> next_state_set;
		for (const auto &state_and_position : current_state) {
			int state = state_and_position.first;
			int position = state_and_position.second;
			
			char char_at_position = input[position];
			
			for (const auto &rule : rules->get_rules_for_state_and_char(state, char_at_position)) {
				int next_state;
				int chars_consumed;
				
				if(rule->match(char_at_position, &chars_consumed, &next_state)) {
					std::pair<int, int> next_state_position = std::pair<int, int>(next_state, position + chars_consumed);
					if(!rule->is_force_occur()) {
						next_state_set.emplace_back(state_and_position);
					}
					next_state_set.emplace_back(next_state_position);
				}
			}
		}
		
		current_state = next_state_set;
	} while(!current_state.empty());
	return !current_state.empty() && rules->contains_accepting_state(map_pairs_to_states(current_state));
}
