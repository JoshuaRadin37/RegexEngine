//
// Created by jradi on 11/1/2019.
//

#include "automaton_factory.h"

automaton *automaton_factory::create_char_automaton(char c) {
	auto output = new automaton(new ruleset());
	int start = output->find_unused_state(), end = output->find_unused_state();
	output->rules->set_start_state(start);
	output->rules->add_accepting_state(end);
	output->rules->add_rule(start, c, end);
	return output;
}

automaton *automaton_factory::create_epsilon_automaton() {
	auto output = new automaton(new ruleset());
	int start = output->find_unused_state(), end = output->find_unused_state();
	output->rules->set_start_state(start);
	output->rules->add_accepting_state(end);
	output->rules->add_epsilon_rule(start, end);
	return output;
}

automaton *automaton_factory::create_rule_automaton(rule *rule) {
	auto rules = new ruleset();
	rules->add_rule(rule);
	rules->set_start_state(rule->get_start_state());
	rules->add_accepting_state(rule->get_end_state());
	
	return new automaton(rules);
}

automaton *automaton_factory::create_union_automaton(automaton *left, automaton *right) {
	auto output = new automaton(new ruleset());
	int start_state = output->find_unused_state();
	auto transpose_left = output->add_automaton(*left);
	auto transpose_right = output->add_automaton(*right);
	
	output->rules->set_start_state(start_state);
	output->rules->add_epsilon_rule(start_state, transpose_left.initial_state);
	output->rules->add_epsilon_rule(start_state, transpose_right.initial_state);
	
	output->rules->add_accepting_state(transpose_left.final_states);
	output->rules->add_accepting_state(transpose_right.final_states);
	
	return output;
}

automaton *automaton_factory::create_union_automaton(const std::vector<automaton *> &vector) {
	if(vector.empty()) return nullptr;
	
	if(vector.size() == 1){
		return vector[0];
	} else{
		auto output = new automaton(new ruleset());
		int start_state = output->find_unused_state();
		output->rules->set_start_state(start_state);
		
		for (const auto &item : vector) {
			auto transpose = output->add_automaton(*item);
			output->rules->add_epsilon_rule(start_state, transpose.initial_state);
			output->rules->add_accepting_state(transpose.final_states);
		}
		
		return output;
	}
}

automaton *automaton_factory::create_concat_automaton(automaton *left, automaton *right) {
	auto output = new automaton(new ruleset());
	
	auto transpose_left = output->add_automaton(*left);
	auto transpose_right = output->add_automaton(*right);
	
	int start_state = transpose_left.initial_state;
	
	output->rules->set_start_state(start_state);
	//output->rules->add_epsilon_rule(start_state, transpose_left.initial_state);
	
	for (const auto &final_state : transpose_left.final_states) {
		output->rules->add_epsilon_rule(final_state, transpose_right.initial_state);
	}
	
	output->rules->add_accepting_state(transpose_right.final_states);
	
	return output;
}

automaton *automaton_factory::create_concat_automaton(const std::vector<automaton *> &a) {
	if(a.empty()) return nullptr;
	
	if(a.size() == 1){
		return a[0];
	} else{
		auto sub = std::vector<automaton *>(&a[0], &a[a.size() - 1]);
		return create_concat_automaton(create_concat_automaton(sub), a.back());
	}
}

automaton *automaton_factory::create_string_automaton(const std::string &str) {
	if(str.empty()) return nullptr;
	if(str.size() == 1) return create_char_automaton(str[0]);
	
	auto last = create_char_automaton(str.back());
	auto before = create_string_automaton(str.substr(0, str.length() - 1));
	
	return create_concat_automaton(before, last);
	
}

automaton *automaton_factory::create_closure_automaton(automaton *a) {
	auto output = new automaton(new ruleset());
	int start_state = output->find_unused_state();
	auto transpose_a = output->add_automaton(*a);
	int end_state = output->find_unused_state();
	
	output->rules->set_start_state(start_state);
	output->rules->add_accepting_state(end_state);
	
	output->rules->add_epsilon_rule(start_state, transpose_a.initial_state);
	output->rules->add_epsilon_rule(start_state, end_state);
	for (const auto &state : transpose_a.final_states) {
		output->rules->add_epsilon_rule(state, end_state);
		output->rules->add_epsilon_rule(state, transpose_a.initial_state);
	}
	
	return output;
}

automaton *automaton_factory::create_one_or_none_automaton(automaton *a) {
	
	auto output = new automaton(new ruleset());
	auto transpose_a = output->add_automaton(*a);
	int start_state = transpose_a.initial_state;
	
	output->rules->set_start_state(start_state);
	output->rules->add_accepting_state(transpose_a.final_states);
	output->rules->add_accepting_state(start_state);
	
	return output;
}

automaton *automaton_factory::create_one_or_more_automaton(automaton *a) {
	return create_concat_automaton(a, create_closure_automaton(a));
}
