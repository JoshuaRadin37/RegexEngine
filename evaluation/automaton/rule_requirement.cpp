//
// Created by jradi on 11/3/2019.
//

#include "rule_requirement.h"


rule_requirement::rule_requirement(bool eps) : is_epsilon(eps? 0b10 : 0b01) {

}

rule_requirement::rule_requirement(int backing_field_int, bool start) : is_epsilon(0) {
	if(start) {
		start_states.insert(backing_field_int);
	}else {
		end_states.insert(backing_field_int);
	}
}

rule_requirement rule_requirement::is_start(int s) {
	return rule_requirement(s, true);
}

rule_requirement rule_requirement::is_end(int e) {
	return rule_requirement(e, false);
}

rule_requirement rule_requirement::is_eps(bool e) {
	return rule_requirement(e);
}

rule_requirement rule_requirement::is_start(std::vector<int> s) {
	if (s.empty()) return rule_requirement();
	if (s.size() == 1) return rule_requirement(s[0]);
	auto sub = std::vector<int>(&s[1], &s[s.size()]);
	return rule_requirement(s.front(), true) & is_start(sub);
}

rule_requirement rule_requirement::is_end(std::vector<int> e) {
	if (e.empty()) return rule_requirement();
	if (e.size() == 1) return rule_requirement(e[0]);
	auto sub = std::vector<int>(&e[1], &e[e.size()]);
	return rule_requirement(e.front(), false) & is_start(sub);
}

rule_requirement rule_requirement::is_start(std::initializer_list<int> s) {
	return is_start(std::vector<int>(s));
}

rule_requirement rule_requirement::is_end(std::initializer_list<int> e) {
	return is_end(std::vector<int>(e));
}

const rule_requirement rule_requirement::operator&(const rule_requirement &other) const {
	rule_requirement output((int) (is_epsilon | other.is_epsilon));
	
	output.start_states.insert(start_states.begin(), start_states.end());
	output.start_states.insert(other.start_states.begin(), other.start_states.end());
	
	output.end_states.insert(end_states.begin(), end_states.end());
	output.end_states.insert(other.end_states.begin(), other.end_states.end());
	
	return output;
}

const rule_requirement rule_requirement::operator!() const {
	rule_requirement output = rule_requirement((int) is_epsilon);
	output.start_states = std::set<int>(start_states);
	output.end_states = std::set<int>(end_states);
	
	output.invert = !output.invert;
	return output;
}

rule_requirement::rule_requirement() {}

rule_requirement rule_requirement::eps = rule_requirement::is_eps(true);

bool rule_requirement::match_requirements(rule *rule) {
	bool eps_match = true, start_match = true, end_match = true;
	switch(is_epsilon) {
		case 0b01:
			eps_match = rule->is_force_occur();
			break;
		case 0b10:
			eps_match = !rule->is_force_occur();
			break;
		case 0b11:
			eps_match = true;
			break;
		default:
			break;
	}
	
	if (!start_states.empty())
		start_match = start_states.find(rule->get_start_state()) != start_states.end();
	
	if(!end_states.empty())
		end_match = end_states.find(rule->get_end_state()) != end_states.end();
	
	
	return (eps_match && start_match && end_match) != invert;
}

rule_requirement::rule_requirement(int backing_field_eps) : is_epsilon(backing_field_eps) {

}
