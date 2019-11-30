//
// Created by jradi on 10/30/2019.
//

#include <algorithm>
#include <map>
#include <set>
#include <utility>
#include <evaluation/rules/wrapper_rule.h>
#include <iostream>
#include <queue>
#include "automaton.h"
#include "vector_print.h"

automaton::automaton(ruleset *rules) : rules(rules) {}

std::vector<int> map_pairs_to_states(const std::vector<std::pair<int, int>>& v) {
	auto output = std::vector<int>();
	for (const auto &item : v) {
		output.push_back(item.first);
	}
	return output;
}

group * automaton::create_group() const{
	return new group(0, get_start_state(), get_accepting_states());
}


template <>
std::ostream& operator<<(std::ostream& os, const std::vector<std::pair<int, int>>& v) {
	os << "[";
	bool first = true;
	for (const std::pair<int, int> &item : v) {
		if(!first) os << ", ";
		else first = false;
		os << "{state: " << item.first << ", position: " << item.second << "}";
	}
	os << "]";
	return os;
}

template <>
std::ostream& operator<< <rule *>(std::ostream& os, const std::vector<rule *>& vector) {
	struct {
		bool operator() (rule* a, rule* b) {
			if(a->get_start_state() == b->get_start_state()) return a->get_end_state() < b->get_end_state();
			return a->get_start_state() < b->get_start_state();
		}
	} custom_less;
	std::vector<rule *> sorted(vector);
	std::sort(sorted.begin(), sorted.end(), custom_less);
	for (const rule* r : sorted) {
		os << "\t" << r->to_string() << std::endl;
	}
	return os;
}


bool automaton::accept(const std::string &start_input, bool full_match) {
	std::vector<std::pair<int, int>> current_state = {std::pair<int, int>(rules->get_start_state(), 0)};
	std::string input(start_input);
	
	
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
		std::cout << "Current states: " << current_state << std::endl;
		std::set<std::pair<int, int>> next_state_set;
		for (const auto &state_and_position : current_state){
			
			
			occured_states.insert(state_and_position);
			
			
			int state = state_and_position.first;
			int position = state_and_position.second;
			
			if((!full_match || position == input.length()) && rules->contains_accepting_state(state))
				return true;
			
			char char_at_position = input[position];
			
			for (const auto &rule : rules->get_rules_for_state_and_char(state, char_at_position)) {
				int next_state;
				int chars_consumed;
				
				if(rule->match(char_at_position, &chars_consumed, &next_state)) {
					std::pair<int, int> next_state_position = std::pair<int, int>(next_state, position + chars_consumed);
					/*if(!my_rule->is_force_occur()) {
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
	} while(!current_state.empty());
	std::cout << "final states: " << current_state << std::endl;
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
	return add_automaton(other, false);
}
automaton::automaton_state_transpose automaton::add_automaton(const automaton &other, bool add_full_integrate) {
	std::map<int, int> old_state_to_new_state_map;
	
	for (const int &state : other.get_used_states()) {
		int new_state = find_unused_state();
		old_state_to_new_state_map[state] = new_state;
	}
	
	for(rule* r : other.rules->get_all_rules()) {
		int start_state = old_state_to_new_state_map[r->start_state];
		int end_state = old_state_to_new_state_map[r->end_state];
		auto new_rule = r->to_wrapper_rule(start_state, end_state);
		
		rules->add_rule(new_rule);
	}
	
	int new_initial_state = old_state_to_new_state_map[other.get_start_state()];
	std::vector<int> end_states;
	for (const auto &item : other.get_accepting_states()) {
		end_states.push_back(old_state_to_new_state_map[item]);
	}
	
	
	
	const automaton_state_transpose &transpose = automaton::automaton_state_transpose(new_initial_state, end_states);
	
	if(!add_full_integrate) integrate_group_data(*(other.g_data), old_state_to_new_state_map);
	else {
		
		const group_data &fixed_data = other.get_group_data();
		integrate_group_data(fixed_data, old_state_to_new_state_map);
	}
	
	return transpose;
}

void automaton::add_self_as_group() {
	g_data->get_groups()->push_back(create_group());
}

void automaton::integrate_group_data(group_data data, std::map<int, int> transpose) {
	group_data fixed(std::move(data));
	for (auto group_ptr : *fixed.get_groups()) {
		group_ptr->set_start_state(transpose[group_ptr->get_start_state()]);
		std::vector<int> fixed_states;
		for (int final_state : group_ptr->get_final_states()) {
			fixed_states.push_back(transpose[final_state]);
		}
		group_ptr->set_final_states(fixed_states);
	}
	this->g_data->integrate_group_info(fixed);
}


void automaton::print_info() const {
	std::vector<int> used = get_used_states();
	std::sort(used.begin(), used.end());
	std::cout << "States: " << used << std::endl;
	std::cout << "Start state: " << get_start_state() << std::endl;
	std::cout << "Accepting states: " << get_accepting_states() << std::endl;
	std::cout << "Groups: " << std::endl;
	group_data data = get_group_data();
	for(auto g : *(data.get_groups())) {
		std::cout << "\t" << g->to_string() << std::endl;
	}
	std::cout << "Rules: " << std::endl;
	std::cout << rules->get_all_rules();
}

bool automaton::has_epsilon_transitions() {
	return !rules->get_epsilon_rules().empty();
}

void automaton::reorder_states() {
	std::vector<int> visited;
	
	std::queue<int> queue;
	queue.push(rules->start_state);
	
	do {
		while (!queue.empty() && std::find(visited.begin(), visited.end(), queue.front()) != visited.end()) {
			queue.pop();
		}
		
		if(queue.empty()) break;
		int current = queue.front();
		queue.pop();
		visited.push_back(current);
		
		std::vector<rule *> f_rules = this->rules->get_rules_for_state(current);
		
		for (const auto &eps_rule : f_rules) {
			int next_state = eps_rule->get_end_state();
			
			if (std::find(visited.begin(), visited.end(), next_state) == visited.end()) {
				queue.push(next_state);
			}
		}
		
		
	} while (!queue.empty());
	
	
	std::map<int, int> delta;
	for (int i = 0; i < visited.size(); ++i) {
		int new_state = i;
		int old_state = visited[i];
		delta.insert({old_state, new_state});
	}
	
	auto new_rules = new ruleset();
	for (const auto &rule : rules->get_all_rules()) {
		auto new_rule = rule->to_wrapper_rule(delta[rule->start_state], delta[rule->end_state]);
		new_rules->add_rule(new_rule);
	}
	
	new_rules->set_start_state(delta[get_start_state()]);
	for(int fs : get_accepting_states()) {
		new_rules->add_accepting_state(delta[fs]);
	}
	
	for(group* g : *g_data->get_groups()) {
		g->set_start_state(delta[g->get_start_state()]);
		std::vector<int> new_final_states(g->get_final_states().size());
		for (int i = 0; i < g->get_final_states().size(); ++i) {
			new_final_states[i] = delta[g->get_final_states()[i]];
		}
		g->set_final_states(new_final_states);
	}
	
	delete this->rules;
	this->rules = new_rules;
}

bool automaton::remove_epsilon_transitions() {
	auto new_rules = new ruleset();
	new_rules->set_start_state(rules->get_start_state());
	
	for (int state : get_used_states()) {
		
		auto eps_from = rules->epsilon_closure(state);
		if(rules->contains_accepting_state(std::vector<int>(eps_from.begin(), eps_from.end()))) {
			new_rules->add_accepting_state(state);
		}
		
		for (int from : eps_from) {
			auto mid_rules = rules->get_rules_that(rule_requirement::is_eps(false) & rule_requirement::is_start(from));
			
			for (rule *mid_rule : mid_rules) {
				
				/*
				auto eps_to = rules->epsilon_closure(mid_rule->end_state);
				for (const auto &to : eps_to) {
					   rule* new_rule = mid_rule->to_wrapper_rule(state, to);
					   new_rules->add_rule(new_rule);
				}
				 */
				
				rule* new_rule = mid_rule->to_wrapper_rule(state, mid_rule->end_state);
				new_rules->add_rule(new_rule);
				
			}
		}
		
		
	}
	
	new_rules->remove_useless_rules();
	new_rules->remove_useless_accepting_states();
	
	delete this->rules;
	this->rules = new_rules;
	
	reorder_states();
	return !has_epsilon_transitions();
}

group_data automaton::get_group_data() const{
	group_data output;
	output.get_groups()->push_back(create_group());
	output.integrate_group_info(*g_data);
	for (int i = 0; i < output.get_groups()->size(); ++i) {
		group* g = (*output.get_groups())[i];
		if(!g->is_has_name()) {
			g->set_id(i);
		}
	}
	return output;
}

